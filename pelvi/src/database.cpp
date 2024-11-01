#include "database.h"

#include "dbinit.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Database::Database( QObject* parent )
  : QObject( parent )
{
}

Database::~Database() { closeDatabase(); }

bool Database::openDatabase( const QString& path )
{
  m_db = QSqlDatabase::addDatabase( "QSQLITE" );
  m_db.setDatabaseName( path );

  if(!m_db.open())
  {
    qDebug() << "Error: connection with database failed";
    return false;
  }
  if(!isDatabaseInitialized( "1" ))
  {
    qDebug() << "Initializing database";
    initializeDatabase();
  }
  qDebug() << "Database: connection ok";
  return true;
}

void Database::closeDatabase()
{
  if(m_db.isOpen())
  {
    m_db.close();
  }
}

bool Database::executeQuery( const QString& queryStr, const QVariantList& args )
{
  QSqlQuery query( m_db );
  query.prepare( queryStr );

  for(int i = 0; i < args.size(); ++i)
  {
    query.bindValue( i, args[ i ] );
  }

  if(!query.exec())
  {
    qDebug() << "Error: query execution failed -" << query.lastError();
    return false;
  }

  return true;
}

bool Database::isDatabaseInitialized( const QString& expectedVersion )
{
  QSqlQuery query( m_db );
  query.prepare( "SELECT version FROM database" );

  if(!query.exec() || !query.next())
  {
    return false;
  }

  QString version = query.value( 0 ).toString();
  return version == expectedVersion;
}

void Database::initializeDatabase()
{
  DbInit initializer;
  initializer.initializeDatabase( m_db );
}

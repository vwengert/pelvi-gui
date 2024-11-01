#include "pelvi.h"
#include "database.h"

class PImpl
{
  public:
    PImpl( QObject* parent = nullptr )
      : database( parent )
    {
    }

    Database database;
};

Pelvi::Pelvi( QObject* parent )
  : QObject( parent )
    , m_pimpl( new PImpl( this ) )
{
  m_pimpl->database.openDatabase( "pelvi.db" );
}

Pelvi::~Pelvi()
{
}
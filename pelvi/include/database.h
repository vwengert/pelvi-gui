#ifndef DATABASE_H
#define DATABASE_H

//#include <QSqlDatabase>
#include <QVariantList>



class Database : public QObject
{
  Q_OBJECT
public:
  explicit Database(QObject *parent = nullptr);
  ~Database();

  Database(const Database &) = delete;
  Database(Database &&) = delete;
  Database &operator=(const Database &) = delete;
  Database &operator=(Database &&) = delete;

  bool openDatabase(const QString &path);
  void closeDatabase();
  bool executeQuery(const QString &queryStr, const QVariantList &args = QVariantList());

private:
  //  QSqlDatabase m_db;
};

#endif // DATABASE_H

#pragma once

#include <QObject>
#include <QSqlDatabase>

class DbInit : public QObject
{
  Q_OBJECT

public:
  explicit DbInit(QObject* parent = nullptr);
  ~DbInit();

  void initializeDatabase(QSqlDatabase& db);

  private:
  void createTables(QSqlDatabase& db);
  void insertInitialData(QSqlDatabase& db);
};
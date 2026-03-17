#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>

class DatabaseManager
{
public:
    static bool initialize(bool pDevResetDatabase = false);
    static QSqlDatabase database();

    DatabaseManager();

    QSqlDatabase connection() const;
    bool execute(const QString& pSql);
    bool beginTransaction();
    bool commit();
    bool rollback();

    static bool deleteTablesForTest();

private:
    static bool openDatabase();
    static bool configureDatabase();
    static bool createTables();
};

#endif // DATABASEMANAGER_H

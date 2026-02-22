#include "databasemanager.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

static const char* CONNECTION_NAME = "HealtTrackConnection";

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::initialize()
{

    if(!openDatabase())
    {
        return false;
    }

    if(!configureDatabase())
    {
        return false;
    }

    if(!createTables())
    {
        return false;
    }

    qDebug() << "Database initialized successfully.";
    return true;
}

QSqlDatabase DatabaseManager::database()
{
    return QSqlDatabase::database(CONNECTION_NAME);
}

QSqlDatabase DatabaseManager::connection() const
{
    return QSqlDatabase::database(CONNECTION_NAME);
}

bool DatabaseManager::execute(const QString &pSql)
{
    QSqlQuery tQuery(connection());
    return tQuery.exec(pSql);
}

bool DatabaseManager::beginTransaction()
{
    return connection().transaction();
}

bool DatabaseManager::commit()
{
    return connection().commit();
}

bool DatabaseManager::rollback()
{
    return connection().rollback();
}

bool DatabaseManager::openDatabase()
{
    if(QSqlDatabase::contains(CONNECTION_NAME))
    {
        return true;
    }

    QString path =QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QString dbPath = path + "/healthtrack.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    db.setDatabaseName(dbPath);

    if(!db.open())
    {
        qCritical() << "Database open error:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database path:" << dbPath;
    return true;
}

bool DatabaseManager::configureDatabase()
{
    QSqlQuery query(database());

    if(!query.exec("PRAGMA foreign_keys = ON;"))
    {
        qCritical() << "Failed to enable foreign keys.";
        return false;
    }

    if(!query.exec("PRAGMA journal_mode = WAL;"))
    {
        qCritical() << "Failed to enable WAL mode";
        return false;
    }

    if(!query.exec("PRAGMA synchronous = NORMAL;"))
    {
        qCritical() << "Failed to set synchronous mode";
        return false;
    }

    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query(database());

    //Daily_entries table
    if(!query.exec(R"(
        CREATE TABLE IF NOT EXISTS daily_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL UNIQUE
        )
    )"))
    {
        qCritical() << query.lastError().text();
        return false;
    }

    //Meal_entries table
    if(!query.exec(R"(
        CREATE TABLE IF NOT EXISTS meal_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            daily_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            FOREIGN KEY(daily_id) REFERENCES daily_entries(id) ON DELETE CASCADE
        )
    )"))
    {
        qCritical() << query.lastError().text();
        return false;
    }

    //Food_entries table
    if(!query.exec(R"(
        CREATE TABLE IF NOT EXISTS foods (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            meal_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            calories REAL NOT NULL,
            protein REAL NOT NULL,
            carbs REAL NOT NULL,
            fat REAL NOT NULL,
            FOREIGN KEY(meal_id) REFERENCES meal_entries(id) OM DELETE CASCADE
        )
    )"))
    {
        qCritical() << query.lastError().text();
        return false;
    }

    //TODO: Add all db tables from here
    return true;
}



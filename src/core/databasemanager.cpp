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

    if(!query.exec(R"(
        CREATE TABLE IF NOT EXISTS food_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE,
            calories_per_100g REAL NOT NULL,
            protein_per_100g REAL NOT NULL,
            carbs_per100g REAL NOT NULL,
            fat_per_100g REAL NOT NULL
        ))"))
    {
        qCritical() << query.lastError().text();
        return false;
    }

    //TODO: Add all db tables from here
    return true;
}



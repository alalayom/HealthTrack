#include "databasemanager.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

static const char* CONNECTION_NAME = "HealthTrackConnection";

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::initialize(bool pDevResetDatabase)
{

    if(!openDatabase())
    {
        return false;
    }

    if(!configureDatabase())
    {
        return false;
    }

#ifdef QT_DEBUG
    if(pDevResetDatabase)
    {
        qDebug() << "DEV MODE: deleting all tables before createTables...";
        if(!deleteTablesForTest())
        {
            qCritical() << "Failed to delete tables for test.";
            return false;
        }
    }
#endif

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

bool DatabaseManager::deleteTablesForTest()
{
    QSqlDatabase tDatabase = database();
    if(!tDatabase.isOpen())
    {
        return false;
    }

    QSqlQuery tQuery(tDatabase);

    //close foreign key constraints for temporary testing
    if(!tQuery.exec("PRAGMA foreign_keys = OFF;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS water_entries;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS foods;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS food_entries;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS meal_entries;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS daily_entries;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS body_segment_metrics;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS body_composition_metrics;"))
    {
        return false;
    }

    if(!tQuery.exec("DROP TABLE IF EXISTS body_measurements;"))
    {
        return false;
    }

    if(!tQuery.exec("PRAGMA foreign_keys = ON;"))
    {
        return false;
    }

    qDebug() << "All tables deleted (DEV MODE).";

    return true;
}

bool DatabaseManager::openDatabase()
{
    if(QSqlDatabase::contains(CONNECTION_NAME))
    {
        QSqlDatabase tDb = QSqlDatabase::database(CONNECTION_NAME);
        if(tDb.isOpen())
        {
            return true;
        }
    }

    QString tPath =QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(tPath);
    QString tDbPath = tPath + "/healthtrack.db";
    QSqlDatabase tDb = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    tDb.setDatabaseName(tDbPath);

    if(!tDb.open())
    {
        qCritical() << "Database open error:" << tDb.lastError().text();
        return false;
    }

    qDebug() << "Database path:" << tDbPath;
    return true;
}

bool DatabaseManager::configureDatabase()
{
    QSqlQuery tQuery(database());

    if(!tQuery.exec("PRAGMA foreign_keys = ON;"))
    {
        qCritical() << "Failed to enable foreign keys.";
        return false;
    }

    if(!tQuery.exec("PRAGMA journal_mode = WAL;"))
    {
        qCritical() << "Failed to enable WAL mode";
        return false;
    }

    if(!tQuery.exec("PRAGMA synchronous = NORMAL;"))
    {
        qCritical() << "Failed to set synchronous mode";
        return false;
    }

    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery tQuery(database());

    //Daily_entries table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS daily_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL UNIQUE,
            notes TEXT
        )
    )"))
    {
        qCritical() << tQuery.lastError().text();
        return false;
    }

    //Meal_entries table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS meal_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            daily_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            FOREIGN KEY(daily_id) REFERENCES daily_entries(id) ON DELETE CASCADE
        )
    )"))
    {
        qCritical() << tQuery.lastError().text();
        return false;
    }

    //foods -> catalog (saved foods)
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS foods(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE,
            calories REAL NOT NULL,
            protein REAL NOT NULL,
            carbs REAL NOT NULL,
            fat REAL NOT NULL
        )
    )"))
    {
        qCritical() << "Failed to create foods: " << tQuery.lastError().text();
        return false;
    }

    //Food_entries table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS food_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            meal_id INTEGER NOT NULL,
            catalog_food_id INTEGER,
            name TEXT NOT NULL,
            calories REAL NOT NULL,
            protein REAL NOT NULL,
            carbs REAL NOT NULL,
            fat REAL NOT NULL,
            FOREIGN KEY(meal_id) REFERENCES meal_entries(id) ON DELETE CASCADE,
            FOREIGN KEY(catalog_food_id) REFERENCES foods(id) ON DELETE SET NULL
        )
    )"))
    {
        qCritical() << tQuery.lastError().text();
        return false;
    }

    //water_entries table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS water_entries (
            date TEXT PRIMARY KEY,
            amount_ml INTEGER NOT NULL DEFAULT 0
        )
    )"))
    {
        qCritical() << "Faield to create water_entries:" << tQuery.lastError().text();
        return false;
    }

    //body_measurements table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS body_measurements(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            measurement_date TEXT NOT NULL UNIQUE
        )
    )"))
    {
        qCritical() << "Failed to create body_measurements:" << tQuery.lastError().text();
        return false;
    }

    //body_composition_metrics table
    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS body_composition_metrics (
            measurement_id INTEGER PRIMARY KEY,
            weight_kg REAL NOT NULL,
            muscle_mass_kg REAL NOT NULL,
            muscle_percentage REAL NOT NULL,
            fat_mass_kg REAL NOT NULL,
            fat_percentage REAL NOT NULL,
            lean_mass_kg REAL NOT NULL,
            body_water_mass_kg REAL NOT NULL,
            body_water_percentage REAL NOT NULL,
            bmi REAL NULL,
            bmr REAL NULL,
            FOREIGN KEY(measurement_id) REFERENCES body_measurements(id) ON DELETE CASCADE
        )
    )"))
    {
        qCritical() << "Failed to create body_composition_metrics:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS body_segment_metrics (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            measurement_id INTEGER NOT NULL,
            segment_name TEXT NOT NULL,
            muscle_mass_kg REAL NOT NULL,
            fat_mass_kg REAL NOT NULL,
            fat_percentage REAL NOT NULL,
            lean_mass_kg REAL NOT NULL,
            FOREIGN KEY(measurement_id) REFERENCES body_measurements(id) ON DELETE CASCADE,
            UNIQUE(measurement_id, segment_name)
        )
    )"))
    {
        qCritical() << "Failed to create body_segment_metrics:" << tQuery.lastError().text();
        return false;
    }

    //Indexes for foreign keys
    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_meal_daily_id
        ON meal_entries(daily_id)
    )"))
    {
        qCritical() << "Failed to create idx_meal_daily_id:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_food_meal_id
        ON food_entries(meal_id)
    )"))
    {
        qCritical() << "Failed to create idx_food_meal_id:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_food_entries_catalog_food_id
        ON food_entries(catalog_food_id)
    )"))
    {
        qCritical() << "Failed to create idx_food_entries_catalog_food_id:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_foods_name
        ON foods(name COLLATE NOCASE)
    )"))
    {
        qCritical() << "Failed to create idx_foods_name:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_body_composition_measurement_id
        ON body_composition_metrics(measurement_id)
    )"))
    {
        qCritical() << "Failed to create idx_body_composition_measurement_id:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_body_segment_measurement_id
        ON body_segment_metrics(measurement_id)
    )"))
    {
        qCritical() << "Failed to create idx_body_segment_measurement_id:" << tQuery.lastError().text();
        return false;
    }

    if(!tQuery.exec(R"(
        CREATE INDEX IF NOT EXISTS idx_body_segment_name
        ON body_segment_metrics(segment_name)
    )"))
    {
        qCritical() << "Failed to create idx_body_segment_name:" << tQuery.lastError().text();
        return false;
    }

    //TODO: Add all db tables from here
    return true;
}

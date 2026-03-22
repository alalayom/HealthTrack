#include "waterrepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QtGlobal>

WaterRepository::WaterRepository(DatabaseManager *pDatabaseManager)
    : mDatabaseManager(pDatabaseManager)
{

}

bool WaterRepository::saveWaterEntry(const WaterEntry &pEntry)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        INSERT OR REPLACE INTO water_entries(date, amount_ml)
        VALUES(?, ?)
    )");

    tQuery.addBindValue(pEntry.getDate().toString(Qt::ISODate));
    tQuery.addBindValue(pEntry.getAmountMl());

    if(!tQuery.exec())
    {
        qWarning() << "saveWaterEntry failed:" << tQuery.lastError().text();
        return false;
    }

    return true;
}

WaterEntry WaterRepository::loadWaterEntry(const QDate &pDate)
{
    WaterEntry tEntry(pDate);

    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        SELECT amount_ml
        FROM water_entries
        WHERE date = ?
    )");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tQuery.exec())
    {
        qWarning() << "loadWater failed:" << tQuery.lastError().text();
        return tEntry;
    }

    if(!tQuery.next())
    {
        return tEntry;
    }

    tEntry.setAmountMl(tQuery.value(0).toInt());
    return tEntry;
}

bool WaterRepository::deleteWaterEntry(const QDate &pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("DELETE FROM water_entries WHERE date = ?");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tQuery.exec())
    {
        qWarning() << "deleteWaterEntry failed:" << tQuery.lastError().text();
        return false;
    }

    return true;
}

bool WaterRepository::addWater(const QDate &pDate, int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return false;
    }

    WaterEntry tEntry = loadWaterEntry(pDate);
    tEntry.addWater(pAmountMl);

    return saveWaterEntry(tEntry);
}

bool WaterRepository::removeWater(const QDate &pDate, int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return false;
    }

    WaterEntry tEntry = loadWaterEntry(pDate);
    tEntry.removeWater(pAmountMl);

    return saveWaterEntry(tEntry);
}

bool WaterRepository::setWaterAmount(const QDate &pDate, int pAmountMl)
{
    if(pAmountMl < 0)
    {
        return false;
    }

    WaterEntry tEntry(pDate);
    tEntry.setAmountMl(pAmountMl);

    return saveWaterEntry(tEntry);
}

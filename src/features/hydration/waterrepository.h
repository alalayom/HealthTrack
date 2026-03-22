#ifndef WATERREPOSITORY_H
#define WATERREPOSITORY_H

#include "waterentry.h"
#include "../../core/databasemanager.h"

class WaterRepository
{
public:
    explicit WaterRepository(DatabaseManager* pDatabaseManager);

    bool saveWaterEntry(const WaterEntry& pEntry);
    WaterEntry loadWaterEntry(const QDate& pDate);
    bool deleteWaterEntry(const QDate& pDate);

    bool addWater(const QDate& pDate, int pAmountMl);
    bool removeWater(const QDate& pDate, int pAmountMl);
    bool setWaterAmount(const QDate& pDate, int pAmountMl);

private:
    DatabaseManager* mDatabaseManager = nullptr;;
};

#endif // WATERREPOSITORY_H

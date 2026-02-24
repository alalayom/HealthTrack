#ifndef NUTRITIONREPOSITORY_H
#define NUTRITIONREPOSITORY_H

#include <QDate>
#include <QList>

#include "dailyentry.h"
#include "../../core/databasemanager.h"

class NutritionRepository final
{
public:
    explicit NutritionRepository(DatabaseManager* pDatabaseManager);
    ~NutritionRepository() = default;

    bool saveDailyEntry(const DailyEntry& pEntry);
    DailyEntry loadDailyEntry(const QDate& pDate);
    bool deleteDailyEntry(const QDate& pDate);

private:
    int ensureDailyId(const QDate& pDate);
    int insertMeal(int pDailyId, const MealEntry& pMeal);
    bool insertFood(int pMealId, const FoodEntry& pFood);

    DatabaseManager* mDatabaseManager = nullptr;

};

#endif // NUTRITIONREPOSITORY_H

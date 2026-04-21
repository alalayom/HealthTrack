#ifndef NUTRITIONREPOSITORY_H
#define NUTRITIONREPOSITORY_H

#include <QDate>
#include <QList>
#include <QVariantList>

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

    bool insertCatalogFood(const FoodEntry& pFood);
    QVariantList searchCatalogFoods(const QString& pSearchText) const;

private:
    int ensureDailyId(const QDate& pDate, const QString& pNotes);
    int insertMeal(int pDailyId, const MealEntry& pMeal);
    bool insertFood(int pMealId, const FoodEntry& pFood);

    DatabaseManager* mDatabaseManager = nullptr;

};

#endif // NUTRITIONREPOSITORY_H

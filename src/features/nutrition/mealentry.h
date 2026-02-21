#ifndef MEALENTRY_H
#define MEALENTRY_H

#include <QList>

#include "foodentry.h"

class MealEntry
{
public:
    MealEntry();
    explicit MealEntry(QString pMealName);

    ~MealEntry();

    const QString& getMealName() const noexcept;
    const QList<FoodEntry>& getFoods() const noexcept;

    void setMealName(QString pMealName);

    void addFood(FoodEntry pFood);
    void removeFood(int pIndex);
    void clearFoods() noexcept;

    double totalCalories() const noexcept;
    double totalProtein() const noexcept;
    double totalCarbs() const noexcept;
    double totalFat() const noexcept;

private:
    QString mMealName;
    QList<FoodEntry> mFoods;
};

#endif // MEALENTRY_H

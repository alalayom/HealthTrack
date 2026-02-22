#ifndef NUTRITIONSERVICE_H
#define NUTRITIONSERVICE_H

#include <QObject>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>

#include "dailyentry.h"
#include "mealentry.h"
#include "foodentry.h"

class NutritionService final : public QObject
{
    Q_OBJECT

public:
    explicit NutritionService(QObject* pParent = nullptr);

    const DailyEntry& dailyEntry() const noexcept;

    QDate getDate() const noexcept;
    void setDate(const QDate& pDate);

    int mealCount() const noexcept;
    MealEntry mealAt(int pMealIndex) const;
    const QList<MealEntry>& getMeals() const noexcept;
    void addMeal(const QString& pMealName);
    void removeMeal(int pMealIndex);
    void clearMeals() noexcept;

    void addFood(int pMealIndex, const QString& pName, double pCalories, double pProtein, double pCarbs, double pFat);
    void removeFood(int pMealIndex, int pFoodIndex);
    void clearFoods(int pMealIndex);

    double totalCalories() const noexcept;
    double totalProtein() const noexcept;
    double totalCarbs() const noexcept;
    double totalFat() const noexcept;

    QVariantList mealsAsVariantList() const;
    QVariantMap dailyTotalAsVariantMap() const;

signals:
    void dateChanged();
    void mealsChanged();
    void totalsChanged();

private:
    static QVariantMap foodToVariant(const FoodEntry& pFood);
    static QVariantMap mealToVariant(const MealEntry& pMeal);
    DailyEntry mDaily;
};

#endif // NUTRITIONSERVICE_H

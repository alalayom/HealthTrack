#ifndef NUTRITIONVIEWMODEL_H
#define NUTRITIONVIEWMODEL_H

#include <QObject>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>

#include "nutritionservice.h"

class NutritionViewModel final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ getDate WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QVariantList meals READ getMeals NOTIFY mealsChanged FINAL)

    Q_PROPERTY(double totalCalories READ getTotalCalories NOTIFY totalCaloriesChanged FINAL)
    Q_PROPERTY(double totalProtein READ getTotalProtein NOTIFY totalProteinChanged FINAL)
    Q_PROPERTY(double totalCarbs READ getTotalCarbs NOTIFY totalCarbsChanged FINAL)
    Q_PROPERTY(double totalFat READ getTotalFat NOTIFY totalFatChanged FINAL)


public:
    explicit NutritionViewModel(NutritionService* pService, QObject* pParent = nullptr);

    QDate getDate() const;
    void setDate(const QDate& pDate);

    QVariantList getMeals() const;

    double getTotalCalories() const;
    double getTotalProtein() const;
    double getTotalCarbs() const;
    double getTotalFat() const;

    Q_INVOKABLE void addMeal(const QString& pMealName);
    Q_INVOKABLE void removeMeal(int pMealIndex);
    Q_INVOKABLE void clearMeals();
    Q_INVOKABLE void addFood(int pMealIndex, const QString& pName, double pCalories, double pProtein, double pCarbs, double pFat);
    Q_INVOKABLE void removeFood(int pMealIndex, int pFoodIndex);
    Q_INVOKABLE void clearFoods(int pMealIndex);

signals:
    void dateChanged();
    void mealsChanged();
    void totalCaloriesChanged();
    void totalProteinChanged();
    void totalCarbsChanged();
    void totalFatChanged();

private:
    void wireSignals();
    NutritionService* mService = nullptr;
};

#endif // NUTRITIONVIEWMODEL_H

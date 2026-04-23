#include "foodportioncalculator.h"

#include <QtGlobal>

FoodEntry FoodPortionCalculator::createPortionedFood(QString pName,
                                                     double pCaloriesPer100g,
                                                     double pProteinPer100g,
                                                     double pCarbsPer100g,
                                                     double pFatPer100g,
                                                     double pGrams)
{
    const double tGrams = sanitizeGrams(pGrams);

    return FoodEntry(std::move(pName),
                     scaleValue(pCaloriesPer100g, tGrams),
                     scaleValue(pProteinPer100g, tGrams),
                     scaleValue(pCarbsPer100g, tGrams),
                     scaleValue(pFatPer100g, tGrams),
                     tGrams);
}

QVariantMap FoodPortionCalculator::createPreview(QString pName,
                                                 double pCaloriesPer100g,
                                                 double pProteinPer100g,
                                                 double pCarbsPer100g,
                                                 double pFatPer100g,
                                                 double pGrams)
{
    const FoodEntry tFood = createPortionedFood(std::move(pName),
                                                pCaloriesPer100g,
                                                pProteinPer100g,
                                                pCarbsPer100g,
                                                pFatPer100g,
                                                pGrams);

    QVariantMap tPreview;
    tPreview["name"] = tFood.getName();
    tPreview["grams"] = tFood.getGrams();
    tPreview["calories"] = tFood.getCalories();
    tPreview["protein"] = tFood.getProtein();
    tPreview["carbs"] = tFood.getCarbs();
    tPreview["fat"] = tFood.getFat();

    return tPreview;
}

double FoodPortionCalculator::sanitizeGrams(double pGrams) noexcept
{
    return qMax(0.0, pGrams);
}

double FoodPortionCalculator::scaleValue(double pValuePer100g, double pGrams) noexcept
{
    return qMax(0.0, pValuePer100g) * sanitizeGrams(pGrams) / 100.0;
}

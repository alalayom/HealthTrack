#ifndef FOODPORTIONCALCULATOR_H
#define FOODPORTIONCALCULATOR_H

#include <QVariantMap>

#include "foodentry.h"

class FoodPortionCalculator final
{
public:
    static FoodEntry createPortionedFood(QString pName,
                                         double pCaloriesPer100g,
                                         double pProteinPer100g,
                                         double pCarbsPer100g,
                                         double pFatPer100g,
                                         double pGrams);

    static QVariantMap createPreview(QString pName,
                                     double pCaloriesPer100g,
                                     double pProteinPer100g,
                                     double pCarbsPer100g,
                                     double pFatPer100g,
                                     double pGrams);

private:
    static double sanitizeGrams(double pGrams) noexcept;
    static double scaleValue(double pValuePer100g, double pGrams) noexcept;
};

#endif // FOODPORTIONCALCULATOR_H

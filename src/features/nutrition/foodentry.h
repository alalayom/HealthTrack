#ifndef FOODENTRY_H
#define FOODENTRY_H

#include <QString>
#include <QtGlobal>

class FoodEntry
{
public:
    FoodEntry();

    FoodEntry(QString pName,
              double pCalories,
              double pProtein,
              double pCarbs,
              double pFat,
              double pGrams = 100.0,
              int pCatalogFoodId = -1);

    ~FoodEntry();

    const QString& getName() const noexcept;
    double getCalories() const noexcept;
    double getProtein() const noexcept;
    double getCarbs() const noexcept;
    double getFat() const noexcept;
    double getGrams() const noexcept;
    int getCatalogFoodId() const noexcept;
    bool hasCatalogFoodId() const noexcept;

    void setName(QString pName);
    void setCalories(double pCalories);
    void setProtein(double pProtein);
    void setCarbs(double pCarbs);
    void setFat(double pFat);
    void setGrams(double pGrams);
    void setCatalogFoodId(int pCatalogFoodId);

private:

    QString mName;
    double mCalories;
    double mProtein;
    double mCarbs;
    double mFat;
    double mGrams;
    int mCatalogFoodId;
};

#endif // FOODENTRY_H

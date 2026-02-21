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
              double pFat);

    ~FoodEntry();

    const QString& getName() const noexcept;
    double getCalories() const noexcept;
    double getProtein() const noexcept;
    double getCarbs() const noexcept;
    double getFat() const noexcept;

    void setName(QString pName);
    void setCalories(double pCalories);
    void setProtein(double pProtein);
    void setCarbs(double pCarbs);
    void setFat(double pFat);

private:

    QString mName;
    double mCalories;
    double mProtein;
    double mCarbs;
    double mFat;
};

#endif // FOODENTRY_H

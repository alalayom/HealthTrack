#ifndef DAILYENTRY_H
#define DAILYENTRY_H

#include <QDate>

#include "mealentry.h"

class DailyEntry
{
public:
    DailyEntry();
    explicit DailyEntry(QDate pDate);

    ~DailyEntry();

    const QDate& getDate() const noexcept;
    void setDate(QDate pDate);

    const QList<MealEntry>& getMeals() const noexcept;
    void addMeal(MealEntry pMeal);
    void removeMeal(int pIndex);
    void clearMeals() noexcept;

    const QString& getNotes() const noexcept;
    void setNotes(QString pNotes);
    void clearNotes() noexcept;

    double totalCalories() const noexcept;
    double totalProtein() const noexcept;
    double totalCarbs() const noexcept;
    double totalFat() const noexcept;

    MealEntry& mealRef(int pIndex);
    const MealEntry& mealRef(int pIndex) const;

private:
    QDate mDate;
    QList<MealEntry> mMeals;
    QString mNotes;
};

#endif // DAILYENTRY_H

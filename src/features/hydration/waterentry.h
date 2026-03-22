#ifndef WATERENTRY_H
#define WATERENTRY_H

#include <QDate>

class WaterEntry
{
public:
    WaterEntry();
    explicit WaterEntry(QDate pDate);

    ~WaterEntry();

    const QDate& getDate() const noexcept;
    int getAmountMl() const noexcept;

    void setDate(QDate pDate);
    void setAmountMl(int pAmountMl);

    void addWater(int pAmountMl);
    void removeWater(int pAmountMl);
    void reset() noexcept;

private:
    QDate mDate;
    int mAmountMl { 0 };
};

#endif // WATERENTRY_H

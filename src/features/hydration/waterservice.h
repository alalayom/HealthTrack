#ifndef WATERSERVICE_H
#define WATERSERVICE_H

#include <QObject>
#include <QDate>

#include "waterentry.h"
#include "../../core/databasemanager.h"
#include "waterrepository.h"

class WaterService final : public QObject
{
    Q_OBJECT

public:
    explicit WaterService(DatabaseManager* pDatabaseManager, QObject* pParent = nullptr);

    const WaterEntry& waterEntry() const noexcept;

    QDate getDate() const noexcept;
    void setDate(const QDate& pDate);

    int getCurrentAmountMl() const noexcept;
    int getGoalAmountMl() const noexcept;
    int getRemainingAmountMl() const noexcept;

    void setGoalAmountMl(int pGoalAmountMl);
    double progress() const noexcept;

    void addWater(int pAmountMl);
    void removeWater(int pAmountMl);
    void setWaterAmount(int pAmountMl);
    void resetWater() noexcept;

    bool saveCurrentDay();
    void loadCurrentDay();

signals:
    void dateChanged();
    void waterChanged();
    void goalChanged();

private:
    DatabaseManager* mDatabaseManager = nullptr;
    WaterRepository mRepository;
    WaterEntry mWater;
    int mGoalAmountMl { 2500 };
};

#endif // WATERSERVICE_H

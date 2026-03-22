#ifndef WATERVIEWMODEL_H
#define WATERVIEWMODEL_H

#include "waterservice.h"

class WaterViewModel final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ getDate WRITE setDate NOTIFY dateChanged FINAL)

    Q_PROPERTY(int currentAmountMl READ getCurrentAmountMl NOTIFY currentAmountMlChanged FINAL)
    Q_PROPERTY(int goalAmountMl READ getGoalAmountMl WRITE setGoalAmountMl NOTIFY goalAmountMlChanged FINAL)
    Q_PROPERTY(int remainingAmountMl READ getRemainingAmountMl NOTIFY remainingAmountMlChanged FINAL)
    Q_PROPERTY(double progress READ getProgress NOTIFY progressChanged FINAL)

    Q_PROPERTY(int selectedCupAmountMl READ getSelectedCupAmountMl WRITE setSelectedCupAmountMl NOTIFY selectedCupAmountMlChanged FINAL)
    Q_PROPERTY(int filledCupCount READ getFilledCupCount NOTIFY filledCupCountChanged FINAL)
    Q_PROPERTY(int targetCupCount READ getTargetCupCount NOTIFY targetCupCountChanged FINAL)

public:
    explicit WaterViewModel(WaterService* pWaterService, QObject* pParent = nullptr);

    QDate getDate() const;
    void setDate(const QDate& pDate);

    int getCurrentAmountMl() const;
    int getGoalAmountMl() const;
    void setGoalAmountMl(int pGoalAmountMl);

    int getRemainingAmountMl() const;
    double getProgress() const;

    int getSelectedCupAmountMl() const;
    void setSelectedCupAmountMl(int pSelectedCupAmountMl);

    int getFilledCupCount() const;
    int getTargetCupCount() const;

    Q_INVOKABLE void addWater(int pAmountMl);
    Q_INVOKABLE void removeWater(int pAmountMl);
    Q_INVOKABLE void setWaterAmount(int pAmountMl);
    Q_INVOKABLE void resetWater();

    Q_INVOKABLE void addSelectedCup();
    Q_INVOKABLE void removeSelectedCup();
    Q_INVOKABLE void toggleCup(int pCupIndex);

signals:
    void dateChanged();

    void currentAmountMlChanged();
    void goalAmountMlChanged();
    void remainingAmountMlChanged();
    void progressChanged();

    void selectedCupAmountMlChanged();
    void filledCupCountChanged();
    void targetCupCountChanged();

private:
    void wireSignals();

    WaterService* mService = nullptr;
    int mSelectedCupAmountMl { 250 };
};

#endif // WATERVIEWMODEL_H

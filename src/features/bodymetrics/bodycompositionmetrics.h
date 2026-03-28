#ifndef BODYCOMPOSITIONMETRICS_H
#define BODYCOMPOSITIONMETRICS_H

class BodyCompositionMetrics
{
public:
    BodyCompositionMetrics();
    explicit BodyCompositionMetrics(double pWeightKg,
                           double pMuscleMassKg,
                           double pMusclePercentage,
                           double pFatMassKg,
                           double pFatPercentage,
                           double pLeanMassKg,
                           double pBodyWaterMassKg,
                           double pBodyWaterPercentage,
                           double pBmi,
                           double pBmr);

    ~BodyCompositionMetrics();

    double getWeightKg() const noexcept;
    void setWeightKg(double pWeightKg) noexcept;

    double getMuscleMassKg() const noexcept;
    void setMuscleMassKg(double pMuscleMassKg) noexcept;

    double getMusclePercentage() const noexcept;
    void setMusclePercentage(double pMusclePercentage) noexcept;

    double getFatMassKg() const noexcept;
    void setFatMassKg(double pFatMassKg) noexcept;

    double getFatPercentage() const noexcept;
    void setFatPercentage(double pFatPercentage) noexcept;

    double getLeanMassKg() const noexcept;
    void setLeanMassKg(double pLeanMassKg) noexcept;

    double getBodyWaterMassKg() const noexcept;
    void setBodyWaterMassKg(double pBodyWaterMassKg) noexcept;

    double getBodyWaterPercentage() const noexcept;
    void setBodyWaterPercentage(double pBodyWaterPercentage) noexcept;

    double getBmi() const noexcept;
    void setBmi(double pBmi) noexcept;

    double getBmr() const noexcept;
    void setBmr(double pBmr) noexcept;

private:
    double mWeightKg;
    double mMuscleMassKg;
    double mMusclePercentage;
    double mFatMassKg;
    double mFatPercentage;
    double mLeanMassKg;
    double mBodyWaterMassKg;
    double mBodyWaterPercentage;
    double mBmi;
    double mBmr;

};

#endif // BODYCOMPOSITIONMETRICS_H

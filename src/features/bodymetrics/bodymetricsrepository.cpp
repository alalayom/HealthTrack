#include "bodymetricsrepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

BodyMetricsRepository::BodyMetricsRepository(DatabaseManager *pDatabaseManager)
    : mDatabaseManager(pDatabaseManager)
{

}

bool BodyMetricsRepository::saveMeasurementEntry(const BodyMeasurementEntry &pEntry)
{
    if(!mDatabaseManager->database().transaction())
    {
        return false;
    }

    int tMeasurementId = ensureMeasurementId(pEntry.getMeasurementDate());
    if(tMeasurementId <= 0)
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    QSqlQuery tDeleteCompositionQuery(mDatabaseManager->database());
    tDeleteCompositionQuery.prepare("DELETE FROM body_composition_metrics WHERE measurement_id = ?");
    tDeleteCompositionQuery.addBindValue(tMeasurementId);

    if(!tDeleteCompositionQuery.exec())
    {
        qCritical() << "delete body_composition_metrics failed:" << tDeleteCompositionQuery.lastError().text();
        mDatabaseManager->database().rollback();
        return false;
    }

    QSqlQuery tDeleteSegmentQuery(mDatabaseManager->database());
    tDeleteSegmentQuery.prepare("DELETE FROM body_segment_metrics WHERE measurement_id = ?");
    tDeleteSegmentQuery.addBindValue(tMeasurementId);

    if(!tDeleteSegmentQuery.exec())
    {
        qCritical() << "delete body_segment_metrics failed:" << tDeleteSegmentQuery.lastError().text();
        mDatabaseManager->database().rollback();
        return false;
    }

    if(!saveCompositionMetrics(tMeasurementId, pEntry.getComposition()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    const BodySegmentAnalysis& tAnalysis = pEntry.getSegmentAnalysis();

    if(!saveSegmentMetrics(tMeasurementId, "trunk", tAnalysis.getTrunk()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    if(!saveSegmentMetrics(tMeasurementId, "right_arm", tAnalysis.getRightArm()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    if(!saveSegmentMetrics(tMeasurementId, "left_arm", tAnalysis.getLeftArm()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    if(!saveSegmentMetrics(tMeasurementId, "right_leg", tAnalysis.getRightLeg()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    if(!saveSegmentMetrics(tMeasurementId, "left_leg", tAnalysis.getLeftLeg()))
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    return mDatabaseManager->database().commit();
}

BodyMeasurementEntry BodyMetricsRepository::loadMeasurementEntry(const QDate &pDate)
{
    BodyMeasurementEntry tEntry;
    tEntry.setMeasurementDate(pDate);

    QSqlQuery tMeasurementQuery(mDatabaseManager->database());
    tMeasurementQuery.prepare("SELECT id FROM body_measurements WHERE measurement_date = ?");
    tMeasurementQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tMeasurementQuery.exec() || !tMeasurementQuery.next())
    {
        return tEntry;
    }

    int tMeasurementId = tMeasurementQuery.value(0).toInt();
    tEntry.setId(tMeasurementId);

    QSqlQuery tCompositionQuery(mDatabaseManager->database());
    tCompositionQuery.prepare(R"(
        SELECT weight_kg,
               muscle_mass_kg,
               muscle_percentage,
               fat_mass_kg,
               fat_percentage,
               lean_mass_kg,
               body_water_mass_kg,
               body_water_percentage,
               bmi,
               bmr
        FROM body_composition_metrics
        WHERE measurement_id = ?
    )");
    tCompositionQuery.addBindValue(tMeasurementId);

    if(tCompositionQuery.exec() && tCompositionQuery.next())
    {
        BodyCompositionMetrics tComposition(
            tCompositionQuery.value(0).toDouble(),
            tCompositionQuery.value(1).toDouble(),
            tCompositionQuery.value(2).toDouble(),
            tCompositionQuery.value(3).toDouble(),
            tCompositionQuery.value(4).toDouble(),
            tCompositionQuery.value(5).toDouble(),
            tCompositionQuery.value(6).toDouble(),
            tCompositionQuery.value(7).toDouble(),
            tCompositionQuery.value(8).toDouble(),
            tCompositionQuery.value(9).toDouble()
        );

        tEntry.setComposition(tComposition);
    }

    BodySegmentAnalysis tAnalysis;
    QSqlQuery tSegmentQuery(mDatabaseManager->database());
    tSegmentQuery.prepare(R"(
        SELECT segment_name,
               muscle_mass_kg,
               fat_mass_kg,
               fat_percentage,
               lean_mass_kg
        FROM body_segment_metrics
        WHERE measurement_id = ?
    )");
    tSegmentQuery.addBindValue(tMeasurementId);

    if(tSegmentQuery.exec())
    {
        while(tSegmentQuery.next())
        {
            const QString tSegmentName = tSegmentQuery.value(0).toString();

            SegmentMetrics tMetrics(
                tSegmentQuery.value(1).toDouble(),
                tSegmentQuery.value(2).toDouble(),
                tSegmentQuery.value(3).toDouble(),
                tSegmentQuery.value(4).toDouble()
            );

            if(tSegmentName == "trunk")
            {
                tAnalysis.setTrunk(tMetrics);
            }
            else if(tSegmentName == "right_arm")
            {
                tAnalysis.setRightArm(tMetrics);
            }
            else if(tSegmentName == "left_arm")
            {
                tAnalysis.setLeftArm(tMetrics);
            }
            else if(tSegmentName == "right_leg")
            {
                tAnalysis.setRightLeg(tMetrics);
            }
            else if(tSegmentName == "left_leg")
            {
                tAnalysis.setLeftLeg(tMetrics);
            }
        }
    }

    tEntry.setSegmentAnalysis(tAnalysis);

    return tEntry;
}

BodyMeasurementEntry BodyMetricsRepository::loadLatestMeasurementEntryOnOrBefore(const QDate &pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        SELECT measurement_date
        FROM body_measurements
        WHERE measurement_date <= ?
        ORDER BY measurement_date DESC
        LIMIT 1
    )");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tQuery.exec() || !tQuery.next())
    {
        BodyMeasurementEntry tEmptyEntry;
        tEmptyEntry.setMeasurementDate(pDate);
        return tEmptyEntry;
    }

    const QDate tFoundDate = QDate::fromString(tQuery.value(0).toString(), Qt::ISODate);
    return loadMeasurementEntry(tFoundDate);
}

bool BodyMetricsRepository::deleteMeasurementEntry(const QDate &pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("DELETE FROM body_measurements WHERE measurement_date = ?");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));
    return tQuery.exec();
}

int BodyMetricsRepository::ensureMeasurementId(const QDate &pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("SELECT id FROM body_measurements WHERE measurement_date = ?");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(tQuery.exec() && tQuery.next())
    {
        return tQuery.value(0).toInt();
    }

    tQuery.prepare("INSERT INTO body_measurements(measurement_date) VALUES(?)");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tQuery.exec())
    {
        qCritical() << "ensureMeasurementId insert failed:" << tQuery.lastError().text();
        return -1;
    }

    return tQuery.lastInsertId().toInt();
}

bool BodyMetricsRepository::saveCompositionMetrics(int pMeasurementId, const BodyCompositionMetrics &pComposition)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        INSERT INTO body_composition_metrics(
            measurement_id,
            weight_kg,
            muscle_mass_kg,
            muscle_percentage,
            fat_mass_kg,
            fat_percentage,
            lean_mass_kg,
            body_water_mass_kg,
            body_water_percentage,
            bmi,
            bmr
        ) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");

    tQuery.addBindValue(pMeasurementId);
    tQuery.addBindValue(pComposition.getWeightKg());
    tQuery.addBindValue(pComposition.getMuscleMassKg());
    tQuery.addBindValue(pComposition.getMusclePercentage());
    tQuery.addBindValue(pComposition.getFatMassKg());
    tQuery.addBindValue(pComposition.getFatPercentage());
    tQuery.addBindValue(pComposition.getLeanMassKg());
    tQuery.addBindValue(pComposition.getBodyWaterMassKg());
    tQuery.addBindValue(pComposition.getBodyWaterPercentage());
    tQuery.addBindValue(pComposition.getBmi());
    tQuery.addBindValue(pComposition.getBmr());

    if(!tQuery.exec())
    {
        qCritical() << "saveCompositionMetrics failed:" << tQuery.lastError().text();
        return false;
    }

    return true;
}

bool BodyMetricsRepository::saveSegmentMetrics(int pMeasurementId, const QString &pSegmentName, const SegmentMetrics &pMetrics)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        INSERT INTO body_segment_metrics(
            measurement_id,
            segment_name,
            muscle_mass_kg,
            fat_mass_kg,
            fat_percentage,
            lean_mass_kg
        ) VALUES(?, ?, ?, ?, ?, ?)
    )");

    tQuery.addBindValue(pMeasurementId);
    tQuery.addBindValue(pSegmentName);
    tQuery.addBindValue(pMetrics.getMuscleMassKg());
    tQuery.addBindValue(pMetrics.getFatMassKg());
    tQuery.addBindValue(pMetrics.getFatPercentage());
    tQuery.addBindValue(pMetrics.getLeanMassKg());

    if(!tQuery.exec())
    {
        qCritical() << "saveSegmentMetrics failed:" << tQuery.lastError().text();
        return false;
    }

    return true;
}

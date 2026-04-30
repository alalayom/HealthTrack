#include "sportrepository.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantMap>

SportRepository::SportRepository(DatabaseManager* pDatabaseManager)
    : mDatabaseManager(pDatabaseManager)
{
}

bool SportRepository::ensureDefaultExercises()
{
    const QList<ExerciseEntry> tDefaults {
        ExerciseEntry(-1, "Bench Press", "Chest"),
        ExerciseEntry(-1, "Incline Dumbbell Press", "Chest"),
        ExerciseEntry(-1, "Cable Fly", "Chest"),
        ExerciseEntry(-1, "Cable Triceps Pushdown", "Triceps"),
        ExerciseEntry(-1, "Overhead Triceps Extension", "Triceps"),
        ExerciseEntry(-1, "Barbell Curl", "Biceps"),
        ExerciseEntry(-1, "Hammer Curl", "Biceps"),
        ExerciseEntry(-1, "Lat Pulldown", "Back"),
        ExerciseEntry(-1, "Seated Row", "Back"),
        ExerciseEntry(-1, "Shoulder Press", "Shoulders"),
        ExerciseEntry(-1, "Lateral Raise", "Shoulders"),
        ExerciseEntry(-1, "Plank", "Core"),
        ExerciseEntry(-1, "Crunch", "Core"),
        ExerciseEntry(-1, "Squat", "Quadriceps"),
        ExerciseEntry(-1, "Leg Press", "Quadriceps"),
        ExerciseEntry(-1, "Romanian Deadlift", "Hamstrings"),
        ExerciseEntry(-1, "Leg Curl", "Hamstrings"),
        ExerciseEntry(-1, "Hip Thrust", "Hips"),
        ExerciseEntry(-1, "Standing Calf Raise", "Calves"),
        ExerciseEntry(-1, "Wrist Curl", "Forearms"),
        ExerciseEntry(-1, "Neck Flexion", "Neck"),
        ExerciseEntry(-1, "Treadmill Run", "Cardio")
    };

    for(const auto& tExercise : tDefaults)
    {
        if(!insertExerciseIfMissing(tExercise))
        {
            return false;
        }
    }

    return true;
}

QList<ExerciseEntry> SportRepository::searchExercises(const QString& pSearchText, const QString& pMuscleGroup) const
{
    QList<ExerciseEntry> tResults;
    QSqlQuery tQuery(mDatabaseManager->database());

    const QString tSearch = pSearchText.trimmed();
    const QString tMuscleGroup = pMuscleGroup.trimmed();

    QString tSql = R"(
        SELECT id, name, muscle_group
        FROM exercises
        WHERE 1 = 1
    )";

    if(!tSearch.isEmpty())
    {
        tSql += " AND name LIKE ?";
    }

    if(!tMuscleGroup.isEmpty())
    {
        tSql += " AND muscle_group = ?";
    }

    tSql += " ORDER BY name COLLATE NOCASE ASC LIMIT 100";

    tQuery.prepare(tSql);

    if(!tSearch.isEmpty())
    {
        tQuery.addBindValue("%" + tSearch + "%");
    }

    if(!tMuscleGroup.isEmpty())
    {
        tQuery.addBindValue(tMuscleGroup);
    }

    if(!tQuery.exec())
    {
        qWarning() << "searchExercises failed:" << tQuery.lastError().text();
        return tResults;
    }

    while(tQuery.next())
    {
        tResults.append(ExerciseEntry(tQuery.value(0).toInt(), tQuery.value(1).toString(), tQuery.value(2).toString()));
    }

    return tResults;
}

QVariantList SportRepository::searchExercisesAsVariantList(const QString& pSearchText, const QString& pMuscleGroup) const
{
    QVariantList tList;
    const QList<ExerciseEntry> tExercises = searchExercises(pSearchText, pMuscleGroup);
    tList.reserve(tExercises.size());

    for(const auto& tExercise : tExercises)
    {
        tList.append(exerciseToVariant(tExercise));
    }

    return tList;
}

bool SportRepository::insertExerciseIfMissing(const ExerciseEntry& pExercise)
{
    const QString tName = pExercise.getName().trimmed();
    const QString tMuscleGroup = pExercise.getMuscleGroup().trimmed();

    if(tName.isEmpty() || tMuscleGroup.isEmpty())
    {
        return false;
    }

    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        INSERT OR IGNORE INTO exercises(name, muscle_group)
        VALUES(?, ?)
    )");
    tQuery.addBindValue(tName);
    tQuery.addBindValue(tMuscleGroup);

    if(!tQuery.exec())
    {
        qWarning() << "insertExerciseIfMissing failed:" << tQuery.lastError().text();
        return false;
    }

    return true;
}

QVariantMap SportRepository::exerciseToVariant(const ExerciseEntry& pExercise)
{
    QVariantMap tMap;
    tMap["id"] = pExercise.getId();
    tMap["name"] = pExercise.getName();
    tMap["muscleGroup"] = pExercise.getMuscleGroup();

    return tMap;
}

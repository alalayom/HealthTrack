#ifndef SPORTREPOSITORY_H
#define SPORTREPOSITORY_H

#include <QList>
#include <QVariantList>
#include <QVariantMap>

#include "exerciseentry.h"
#include "../../core/databasemanager.h"

class SportRepository final
{
public:
    explicit SportRepository(DatabaseManager* pDatabaseManager);

    bool ensureDefaultExercises();

    QList<ExerciseEntry> searchExercises(const QString& pSearchText, const QString& pMuscleGroup) const;
    QVariantList searchExercisesAsVariantList(const QString& pSearchText, const QString& pMuscleGroup) const;

private:
    bool insertExerciseIfMissing(const ExerciseEntry& pExercise);
    static QVariantMap exerciseToVariant(const ExerciseEntry& pExercise);

    DatabaseManager* mDatabaseManager = nullptr;
};

#endif // SPORTREPOSITORY_H

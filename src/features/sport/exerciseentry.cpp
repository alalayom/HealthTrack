#include "exerciseentry.h"

#include <utility>

ExerciseEntry::ExerciseEntry()
    : mId(-1)
    , mName("")
    , mMuscleGroup("")
{
}

ExerciseEntry::ExerciseEntry(int pId, QString pName, QString pMuscleGroup)
    : mId(pId)
    , mName(std::move(pName))
    , mMuscleGroup(std::move(pMuscleGroup))
{
}

int ExerciseEntry::getId() const noexcept
{
    return mId;
}

const QString& ExerciseEntry::getName() const noexcept
{
    return mName;
}

const QString& ExerciseEntry::getMuscleGroup() const noexcept
{
    return mMuscleGroup;
}

void ExerciseEntry::setId(int pId)
{
    mId = pId;
}

void ExerciseEntry::setName(QString pName)
{
    mName = std::move(pName);
}

void ExerciseEntry::setMuscleGroup(QString pMuscleGroup)
{
    mMuscleGroup = std::move(pMuscleGroup);
}

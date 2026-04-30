#include "sportservice.h"

SportService::SportService(DatabaseManager* pDatabaseManager, QObject* pParent)
    : QObject(pParent)
    , mRepository(pDatabaseManager)
{
}

bool SportService::ensureDefaultExercises()
{
    const bool tSuccess = mRepository.ensureDefaultExercises();
    if(tSuccess)
    {
        emit exercisesChanged();
    }

    return tSuccess;
}

QString SportService::getSearchText() const
{
    return mSearchText;
}

void SportService::setSearchText(const QString& pSearchText)
{
    const QString tSearchText = pSearchText.trimmed();
    if(mSearchText == tSearchText)
    {
        return;
    }

    mSearchText = tSearchText;

    emit filtersChanged();
    emit exercisesChanged();
}

QString SportService::getSelectedMuscleGroup() const
{
    return mSelectedMuscleGroup;
}

void SportService::setSelectedMuscleGroup(const QString& pMuscleGroup)
{
    const QString tMuscleGroup = pMuscleGroup.trimmed();
    if(mSelectedMuscleGroup == tMuscleGroup)
    {
        return;
    }

    mSelectedMuscleGroup = tMuscleGroup;

    emit filtersChanged();
    emit exercisesChanged();
}

QVariantList SportService::filteredExercises() const
{
    return mRepository.searchExercisesAsVariantList(mSearchText, mSelectedMuscleGroup);
}

#include "sportviewmodel.h"

SportViewModel::SportViewModel(SportService* pService, QObject* pParent)
    : QObject(pParent)
    , mService(pService)
{
    Q_ASSERT(mService);
    wireSignals();
}

QString SportViewModel::getSearchText() const
{
    return mService->getSearchText();
}

void SportViewModel::setSearchText(const QString& pSearchText)
{
    mService->setSearchText(pSearchText);
}

QString SportViewModel::getSelectedMuscleGroup() const
{
    return mService->getSelectedMuscleGroup();
}

void SportViewModel::setSelectedMuscleGroup(const QString& pMuscleGroup)
{
    mService->setSelectedMuscleGroup(pMuscleGroup);
}

QVariantList SportViewModel::getFilteredExercises() const
{
    return mService->filteredExercises();
}

void SportViewModel::clearExerciseFilters()
{
    mService->setSearchText("");
    mService->setSelectedMuscleGroup("");
}

void SportViewModel::wireSignals()
{
    connect(mService, &SportService::filtersChanged, this, &SportViewModel::searchTextChanged);
    connect(mService, &SportService::filtersChanged, this, &SportViewModel::selectedMuscleGroupChanged);
    connect(mService, &SportService::exercisesChanged, this, &SportViewModel::filteredExercisesChanged);
}

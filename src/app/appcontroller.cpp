#include "appcontroller.h"

#include <QDebug>

AppController::AppController(QObject *pParent)
    : QObject(pParent)
    , mAppState(this)
    , mNavigationManager(this)
    , mNutritionService(&mDatabaseManager, this)
    , mNutritionViewModel(&mNutritionService, this)
    , mWaterService(&mDatabaseManager, this)
    , mWaterViewModel(&mWaterService, this)
    , mBodyMetricsService(&mDatabaseManager, this)
    , mBodyMetricsViewModel(&mBodyMetricsService, this)
{

}

bool AppController::initialize(bool pDevResetDatabase)
{
    if(!mDatabaseManager.initialize(pDevResetDatabase))
    {
        qCritical() << "Database initialization failed.";
        return false;
    }

    setupDependencies();

    mNutritionViewModel.setDate(mAppState.getSelectedDate());
    mWaterViewModel.setDate(mAppState.getSelectedDate());
    mBodyMetricsViewModel.setDate(mAppState.getSelectedDate());

    qDebug() << "AppController initialized successfully.";
    return true;
}

AppState* AppController::getAppState()
{
    return &mAppState;
}

NavigationManager* AppController::getNavigationManager()
{
    return &mNavigationManager;
}

NutritionViewModel* AppController::getNutritionViewModel()
{
    return &mNutritionViewModel;
}

WaterViewModel* AppController::getWaterViewModel()
{
    return &mWaterViewModel;
}

BodyMetricsViewModel* AppController::getBodyMetricsViewModel()
{
    return &mBodyMetricsViewModel;
}

void AppController::setupDependencies()
{
    QObject::connect(
        &mAppState,
        &AppState::selectedDateChanged,
        this,
        [this](const QDate& pDate)
        {
            mNutritionViewModel.setDate(pDate);
            mWaterViewModel.setDate(pDate);
            mBodyMetricsViewModel.setDate(pDate);
        }
    );
}



#include "appcontroller.h"

#include <QDebug>

AppController::AppController(QObject *pParent)
    : QObject(pParent)
    , mAppState(this)
    , mNavigationManager(this)
    , mNutritionService(&mDatabaseManager, this)
    , mNutritionViewModel(&mNutritionService, this)
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

    qDebug() << "AppController initialized successfully.";
    return true;
}

AppState *AppController::getAppState()
{
    return &mAppState;
}

NavigationManager *AppController::getNavigationManager()
{
    return &mNavigationManager;
}

NutritionViewModel *AppController::getNutritionViewModel()
{
    return &mNutritionViewModel;
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
        }
    );

}

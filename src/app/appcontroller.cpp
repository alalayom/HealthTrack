#include "appcontroller.h"

#include <QDebug>

AppController::AppController(QObject *pParent)
    : QObject(pParent)
    , mAppState()
    , mNavigationManager()
    , mNutritionService(&mDatabaseManager, this)
    , mNutritionViewModel(&mNutritionService, this)
{

}

bool AppController::initialize(bool pDevResetDatabase)
{
    if(!mDatabaseManager.initialize())
    {
        qCritical() << "Database initialization failed.";
        return false;
    }

//works only in debug not in release
#ifdef QT_DEBUG
    if(pDevResetDatabase)
    {
        qDebug() << "DEV MODE: deleting all tables...";
        mDatabaseManager.deleteTablesForTest();

        if(!mDatabaseManager.initialize())
        {
            qCritical() << "Database re-initialization failed.";
            return false;
        }
    }
#endif

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

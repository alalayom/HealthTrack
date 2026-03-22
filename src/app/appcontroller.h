#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "../core/databasemanager.h"
#include "../core/appsettingsmanager.h"

#include "appstate.h"
#include "navigationmanager.h"

#include "../features/nutrition/nutritionservice.h"
#include "../features/nutrition/nutritionviewmodel.h"

#include "../features/hydration/waterservice.h"
#include "../features/hydration/waterviewmodel.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AppState* appState READ getAppState CONSTANT)
    Q_PROPERTY(NavigationManager* navigationManager READ getNavigationManager CONSTANT)
    Q_PROPERTY(NutritionViewModel* nutritionViewModel READ getNutritionViewModel CONSTANT)
    Q_PROPERTY(WaterViewModel* waterViewModel READ getWaterViewModel CONSTANT)

public:
    explicit AppController(QObject* pParent = nullptr);

    bool initialize(bool pDevResetDatabase = false);

    AppState* getAppState();
    NavigationManager* getNavigationManager();
    NutritionViewModel* getNutritionViewModel();
    WaterViewModel* getWaterViewModel();

private:
    void setupDependencies();

    DatabaseManager mDatabaseManager;
    AppSettingsManager mAppSettingsManager;
    AppState mAppState;
    NavigationManager mNavigationManager;

    NutritionService mNutritionService;
    NutritionViewModel mNutritionViewModel;

    WaterService mWaterService;
    WaterViewModel mWaterViewModel;
};

#endif // APPCONTROLLER_H

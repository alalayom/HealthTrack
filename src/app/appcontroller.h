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

#include "../features/bodymetrics/bodymetricsservice.h"
#include "../features/bodymetrics/bodymetricsviewmodel.h"

#include "../features/sport/sportservice.h"
#include "../features/sport/sportviewmodel.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AppState* appState READ getAppState CONSTANT)
    Q_PROPERTY(NavigationManager* navigationManager READ getNavigationManager CONSTANT)
    Q_PROPERTY(NutritionViewModel* nutritionViewModel READ getNutritionViewModel CONSTANT)
    Q_PROPERTY(WaterViewModel* waterViewModel READ getWaterViewModel CONSTANT)
    Q_PROPERTY(BodyMetricsViewModel* bodyMetricsViewModel READ getBodyMetricsViewModel CONSTANT)
    Q_PROPERTY(SportViewModel* sportViewModel READ getSportViewModel CONSTANT)

public:
    explicit AppController(QObject* pParent = nullptr);

    bool initialize(bool pDevResetDatabase = false);

    AppState* getAppState();
    NavigationManager* getNavigationManager();
    NutritionViewModel* getNutritionViewModel();
    WaterViewModel* getWaterViewModel();
    BodyMetricsViewModel *getBodyMetricsViewModel();
    SportViewModel* getSportViewModel();

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

    BodyMetricsService mBodyMetricsService;
    BodyMetricsViewModel mBodyMetricsViewModel;

    SportService mSportService;
    SportViewModel mSportViewModel;
};

#endif // APPCONTROLLER_H

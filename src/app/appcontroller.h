#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "../core/databasemanager.h"
#include "../core/appsettingsmanager.h"

#include "appstate.h"
#include "navigationmanager.h"

#include "../features/nutrition/nutritionservice.h"
#include "../features/nutrition/nutritionviewmodel.h"

class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AppState* appState READ getAppState CONSTANT)
    Q_PROPERTY(NavigationManager* navigationManager READ getNavigationManager CONSTANT)
    Q_PROPERTY(NutritionViewModel* nutritionViewModel READ getNutritionViewModel CONSTANT)

public:
    explicit AppController(QObject* pParent = nullptr);

    bool initialize(bool pDevResetDatabase = false);

    AppState* getAppState();
    NavigationManager* getNavigationManager();
    NutritionViewModel* getNutritionViewModel();

private:
    void setupDependencies();

    DatabaseManager mDatabaseManager;
    AppSettingsManager mAppSettingsManager;
    AppState mAppState;
    NavigationManager mNavigationManager;
    NutritionService mNutritionService;
    NutritionViewModel mNutritionViewModel;

};

#endif // APPCONTROLLER_H

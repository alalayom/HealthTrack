cmake_minimum_required(VERSION 3.16)

project(HealthTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    QuickControls2
    Sql
)

qt_standard_project_setup(REQUIRES 6.8)

if(ANDROID)
    set(CMAKE_SYSTEM_VERSION 34)
endif()

qt_add_executable(appHealthTrack
    main.cpp
)

qt_add_qml_module(appHealthTrack
    URI HealthTrack
    VERSION 1.0
    QML_FILES

        QML/Main/Main.qml
        QML/Main/LoginPage.qml
        QML/Main/HomeScreen.qml

        QML/Nutrition/NutritionMain.qml
        QML/Nutrition/MealDetails.qml
        QML/Nutrition/AddFood.qml

        QML/Sport/SportMain.qml

        QML/Sleep/SleepMain.qml

        QML/Profile/ProfileMain.qml

        QML/Settings/SettingsMain.qml

        QML/Statistics/StatisticsMain.qml

        SOURCES src/app/appcontroller.h src/app/appcontroller.cpp
        SOURCES src/app/navigationmanager.h src/app/navigationmanager.cpp
        SOURCES src/app/appstate.h src/app/appstate.cpp

        SOURCES src/core/databasemanager.h src/core/databasemanager.cpp
        SOURCES src/core/appsettingsmanager.h src/core/appsettingsmanager.cpp
        SOURCES src/core/dateutils.h src/core/dateutils.cpp
        SOURCES src/core/unitconverter.h src/core/unitconverter.cpp

        SOURCES src/features/nutrition/foodentry.h src/features/nutrition/foodentry.cpp
        SOURCES src/features/nutrition/mealentry.h src/features/nutrition/mealentry.cpp
        SOURCES src/features/nutrition/dailyentry.h src/features/nutrition/dailyentry.cpp
        SOURCES src/features/nutrition/nutritionrepository.h src/features/nutrition/nutritionrepository.cpp
        SOURCES src/features/nutrition/nutritionservice.h src/features/nutrition/nutritionservice.cpp
        SOURCES src/features/nutrition/nutritionviewmodel.h src/features/nutrition/nutritionviewmodel.cpp

        SOURCES src/features/sport/exerciseentry.h src/features/sport/exerciseentry.cpp
        SOURCES src/features/sport/workoutentry.h src/features/sport/workoutentry.cpp
        SOURCES src/features/sport/sportrepository.h src/features/sport/sportrepository.cpp
        SOURCES src/features/sport/sportservice.h src/features/sport/sportservice.cpp
        SOURCES src/features/sport/sportviewmodel.h src/features/sport/sportviewmodel.cpp

        SOURCES src/features/sleep/sleepentry.h src/features/sleep/sleepentry.cpp
        SOURCES src/features/sleep/sleeprepository.h src/features/sleep/sleeprepository.cpp
        SOURCES src/features/sleep/sleepservice.h src/features/sleep/sleepservice.cpp
        SOURCES src/features/sleep/sleepviewmodel.h src/features/sleep/sleepviewmodel.cpp

        SOURCES src/features/hydration/waterentry.h src/features/hydration/waterentry.cpp
        SOURCES src/features/hydration/waterrepository.h src/features/hydration/waterrepository.cpp
        SOURCES src/features/hydration/waterservice.h src/features/hydration/waterservice.cpp
        SOURCES src/features/hydration/waterviewmodel.h src/features/hydration/waterviewmodel.cpp

        SOURCES src/features/profile/userprofile.h src/features/profile/userprofile.cpp
        SOURCES src/features/profile/profilerepository.h src/features/profile/profilerepository.cpp
        SOURCES src/features/profile/profileservice.h src/features/profile/profileservice.cpp
        SOURCES src/features/profile/profileviewmodel.h src/features/profile/profileviewmodel.cpp

        SOURCES src/features/settings/settingsviewmodel.h src/features/settings/settingsviewmodel.cpp

        SOURCES src/features/statistics/statisticsservice.h src/features/statistics/statisticsservice.cpp
        SOURCES src/features/statistics/statisticsviewmodel.h src/features/statistics/statisticsviewmodel.cpp
        SOURCES src/features/statistics/statisticsrepository.h src/features/statistics/statisticsrepository.cpp

        SOURCES src/features/bodymetrics/bodymeasuremententry.h src/features/bodymetrics/bodymeasuremententry.cpp
        SOURCES src/features/bodymetrics/bodycompositionmetrics.h src/features/bodymetrics/bodycompositionmetrics.cpp
        SOURCES src/features/bodymetrics/segmentmetrics.h src/features/bodymetrics/segmentmetrics.cpp
        SOURCES src/features/bodymetrics/bodymetricsrepository.h src/features/bodymetrics/bodymetricsrepository.cpp
        SOURCES src/features/bodymetrics/bodysegmentanalysis.h src/features/bodymetrics/bodysegmentanalysis.cpp
        SOURCES src/features/bodymetrics/bodymetricsservice.h src/features/bodymetrics/bodymetricsservice.cpp
        SOURCES src/features/bodymetrics/bodymetricsviewmodel.h src/features/bodymetrics/bodymetricsviewmodel.cpp



)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHealthTrack PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHealthTrack
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHealthTrack PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appHealthTrack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

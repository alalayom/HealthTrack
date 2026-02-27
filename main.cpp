#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlEngine>

#include "src/app/appcontroller.h"
#include "src/app/navigationmanager.h"

#include <android/log.h>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "MAIN EXECUTED");

    //Save NavigationManager enum type for qml for page indexing
    qmlRegisterUncreatableType<NavigationManager>(
        "HealthTrack", 1, 0,
        "NavigationManager",
        "NavigationManager is exposed via appController; this registration is for enum access only."
    );

    //App Controller(DB + Settings + ViewModels, for dev state give true, for release give false
    AppController tController;
    if(!tController.initialize(true))
    {
        __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "AppController initialization failed");
        return -1;
    }

    //Application engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("appController", &tController);
    engine.loadFromModule("HealthTrack", "Main");

    if (engine.rootObjects().isEmpty())
    {
        __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "QML rootObjects is empty - load failed?");
        return -1;
    }

    return app.exec();
}

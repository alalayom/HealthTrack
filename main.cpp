#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "src/app/appcontroller.h"

#include <android/log.h>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "MAIN EXECUTED");

    //App Controller(DB + Settings + ViewModels, for dev state give true, for release give false
    AppController tController;
    if(!tController.initialize(true))
    {
        qCritical() << "AppController initialization failed.";
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

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "src/core/databasemanager.h"

#include <android/log.h>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    //DB
    __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "MAIN EXECUTED");
    if (!DatabaseManager::initialize())
    {
        qCritical() << "Database initialization failed.";
        return -1;
    }

    //DEVELOPER STAGE ONLY, DELETE BEFORE RELEASE
    DatabaseManager::deleteTablesForTest();
    DatabaseManager::initialize();

    //Application engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("HealthTrack", "Main");

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DDSManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create DDS Manager
    DDSManager ddsManager;
    if (!ddsManager.init()) {
        return -1;
    }

    // Start receiving messages
    ddsManager.startReceiving();

    // Initialize QML engine
    QQmlApplicationEngine engine;
    
    // Expose our DDS manager to QML
    engine.rootContext()->setContextProperty("ddsManager", &ddsManager);
    
    // Load main QML file
    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
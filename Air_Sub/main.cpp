#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Controller controller;
    engine.rootContext()->setContextProperty("controller",&controller);
    engine.load(QUrl(QStringLiteral("qrc:/Login.qml")));

    return app.exec();
}

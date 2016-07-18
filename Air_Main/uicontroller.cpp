#include "uicontroller.h"

UIController::UIController()
{
    engine = new QQmlApplicationEngine();
    engine->rootContext()->setContextProperty("loginController",&loginController);
    engine->rootContext()->setContextProperty("controller",&controller);
    controller.setEngine(engine);
    engine->rootContext()->setContextProperty("subModel",QVariant::fromValue(controller.getSubModel()));
    engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(controller.getDiaryModel()));
    engine->rootContext()->setContextProperty("requestModel",QVariant::fromValue(controller.getRequestQue()));
    //QQmlComponent component(&engine,QUrl::fromLocalFile("Login.qml"));
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    //engine.destroyed();
}

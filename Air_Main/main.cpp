#include "uicontroller.h"

QString username = "123";//当前登录的用户名

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localHost");
    db.setDatabaseName("AirMain.db");
    db.setUserName("admin");
    db.setPassword("admin");
    if(db.open())
    {
        qDebug()<<"Database open!";
    }
    else
    {
        qDebug()<<"Database open error";
    }


    UIController start;
    //QDeclarativeView view;
    //设置窗体无边框
    //view.setSource(QUrl::fromLocalFile("Login.qml"));

     //view.setWindowFlags(Qt::FramelessWindowHint);

     //设置整个窗体背景为透明
     //view.setAttribute(Qt::WA_TranslucentBackground);
     //view.setStyleSheet("background:transparent;");

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("localHost");
//    db.setDatabaseName("AirMain.db");
//    db.setUserName("admin");
//    db.setPassword("admin");
//    if(db.open())
//    {
//        qDebug()<<"Database open!";
//    }
//    else
//    {
//        qDebug()<<"Database open error";
//    }
//    LoginController loginController;
//    QQmlApplicationEngine * engine = new QQmlApplicationEngine();
//    Controller controller;

//    engine->rootContext()->setContextProperty("loginController",&loginController);
//    engine->rootContext()->setContextProperty("controller",&controller);
//    engine->rootContext()->setContextProperty("subModel",QVariant::fromValue(controller.getSubModel()));
//    engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(controller.getDiaryModel()));
//    engine->rootContext()->setContextProperty("requestModel",QVariant::fromValue(controller.getRequestQue()));
//    //QQmlComponent component(&engine,QUrl::fromLocalFile("Login.qml"));

//    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
//    //engine.destroyed();

    return app.exec();
}

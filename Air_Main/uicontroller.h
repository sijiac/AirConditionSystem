#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QGuiApplication>
//#include <QQmlComponent>
#include "logincontroller.h"
#include "controller.h"

class UIController
{
public:
    UIController();
private:
    LoginController loginController;
    QQmlApplicationEngine * engine;
    Controller controller;
};

#endif // UICONTROLLER_H

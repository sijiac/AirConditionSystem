#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "database.h"
#include "mangermapper.h"
#include "tools.h"

extern QString username;//当前登录的用户名

class LoginController:public QObject
{
    Q_OBJECT
public:
    explicit LoginController(QObject *parent = 0);
    ~LoginController();

    Q_INVOKABLE bool tryLogin(const QString &id,const QString &password);
public slots:
    void refresh(){
        qDebug()<<"Called the C++ slot";
    }
private:
    MangerMapper * mapper;
};

#endif // LOGINCONTROLLER_H

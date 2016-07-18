#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "substate.h"
#include <qtimer.h>
#include <Qtime>
#include "socketoperate.h"

class Controller:public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    Q_INVOKABLE void setController(const QString &IpAddress,const QString &subIpAddress,const int &subPortNum,const int &roomID);
    Q_INVOKABLE QString getInnerTemp(){
        return QString::number(sub->getNewTemp(),'f',1);
    }
    Q_INVOKABLE QString getObjectTemp(){
        return QString::number(sub->getObjectTemp(),'f',1);
    }
    Q_INVOKABLE int getWindRate(){
        return sub->getWindRate().toInt();
    }
    Q_INVOKABLE QString getMode(){
        //qDebug()<<"*************:"<<sub->getMode();
        if(sub->getMode() == "1")   return QString("制冷");
        else return QString("制热");
    }
    Q_INVOKABLE QString getLocalIp(){
        return sender->getLocalIp();
    }
    Q_INVOKABLE QString getMainIp(){
        return sender->getMainIp();
    }
    Q_INVOKABLE int getPortNum(){
        return sender->getPortNum();
    }
    Q_INVOKABLE QString getTotalMoney(){
        return QString::number(sub->GetMoney(),'f',1);
    }
    Q_INVOKABLE QString getCurTime(){
        return sub->getcurTime().toString();
    }
    Q_INVOKABLE int getRoomId(){
        return sub->getID();
    }
    Q_INVOKABLE QString getToatalVoltage(){
        return QString::number(sub->GetMoney()/5.0,'f',1);
    }
    Q_INVOKABLE void addTargetTemp(){
        if(sub->getMode() == "1"){
            if(sub->getObjectTemp() >= 25.0)    return ;//25位制冷模式的温度上限
            else if(sub->getObjectTemp() + 1 >= 25.0)  sub->setObjectTemp(25);
            else sub->setObjectTemp(sub->getObjectTemp() + 1);
        }else if(sub->getMode() == "0"){
            if(sub->getObjectTemp() >= 30.0)    return ;//30为制热模式的温度上限
            else if(sub->getObjectTemp() + 1 >= 30.0)  sub->setObjectTemp(30);
            else sub->setObjectTemp(sub->getObjectTemp() + 1);
        }else{
            qDebug()<<"模式错误";
        }
    }
    Q_INVOKABLE void reduceTargetTemp(){
        qDebug()<<"mode:"<<sub->getMode();
        if(sub->getMode() == "1"){
            if(sub->getObjectTemp() <= 18.0)    return ;//25位制冷模式的温度上限
            else if(sub->getObjectTemp() - 1 <= 18.0)  sub->setObjectTemp(18);
            else sub->setObjectTemp(sub->getObjectTemp() - 1);
        }else if(sub->getMode() == "0"){
            if(sub->getObjectTemp() <= 25.0)    return ;//30为制热模式的温度上限
            else if(sub->getObjectTemp() - 1 <= 25.0)  sub->setObjectTemp(25);
            else sub->setObjectTemp(sub->getObjectTemp() - 1);
        }else{
            qDebug()<<"模式错误";
        }
    }
    Q_INVOKABLE void setWindRate(int index){
        sub->setWindRate(QString("%1").arg(index));
    }


    QUdpSocket *udpSocket_recv;
    void StartService(float objictTemp,QString Rate);
    void Close();
    void getLog();
    SubInfo getsubInfo();
private slots:
    void timerUp();
    //void DisconnectTimeUp();
    void receive();
private:
    void sleep(unsigned int ms);
    SubState *sub;
    SocketOperate *sender;
    QTimer *timer;
    //QTimer *Reply_timer;
    //void sleep(unsigned int msec);
};

#endif // CONTROLLER_H

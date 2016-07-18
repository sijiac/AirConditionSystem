#ifndef SOCKTOPERATE_H
#define SOCKTOPERATE_H

#include <QtNetwork>
#include <QDebug>
#include <QObject>
//#include <QHostInfo>

#define localIP "172.27.35.1"

class SocktOperate:public QObject
{
public:
    SocktOperate();
    ~SocktOperate();

    //发送刷新频率 F
    void sendMessage(QString ipAddress,int portNum,int frequency);
    //发送主控机模式,mode "1"表示制冷 "0"表示制热      M
    void sendMessage(QString ipAddress,int portNum,QString mode);
    //发送当前时间    T
    void sendMessage(QString ipAddress,int portNum,QDateTime time);
    //发送时间比例    R
    void sendMessage(QString ipAddress,int portNum,int timeRate,int nothing);
    //发送从控机初始化温度    I
    void sendMessage(QString ipAddress,int portNum,float subInitalState);
    //发送从控机当前费用 L
    void sendMessage(QString ipAddress,int portNum,float use,float cost);
    //发送回复从控机的空调风信息
    void sendMessage(QString ipAddress,int portNum,QString windSpeed,float temp);
    //发送关机帧 G
    void sendMessage(QString ipAddress,int portNum);

private slots:
    //void receive();
    //void sendMessage();
private:
    //QUdpSocket * udpSocketReceive;
    QUdpSocket * udpSocketSend;
    QString localIpAddress = QString(localIP);
    int localPortNum = 6665;
};

#endif // SOCKTOPERATE_H

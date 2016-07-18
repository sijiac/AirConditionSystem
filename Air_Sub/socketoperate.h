#ifndef SOCKETOPERATE_H
#define SOCKETOPERATE_H
#include <QtNetwork>
#include <QString>

class SocketOperate
{
private:
    QString IpAddress;
    QString subIpAddress;
    int subPortNum;
public:
    SocketOperate(QString IP,QString subIP,int subport);

    QString getLocalIp(){
        return subIpAddress;
    }
    QString getMainIp(){
        return IpAddress;
    }
    int getPortNum(){
        return subPortNum;
    }

    QUdpSocket *udpSocket_send;

    void sendmessage(int Messagelen,QString Messagetype,float curTemp,float ObjTemp,QString speed,int num);
};

#endif // SOCKETOPERATE_H

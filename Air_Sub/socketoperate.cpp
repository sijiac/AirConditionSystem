#include "socketoperate.h"

SocketOperate::SocketOperate(QString IP,QString subIP,int subport)
{
    IpAddress=IP;
    subIpAddress=subIP;
    subPortNum=subport;

    udpSocket_send=new QUdpSocket();

}
void SocketOperate::sendmessage(int Messagelen,QString Messagetype,float curTemp,float ObjTemp,QString speed,int num)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    QString group="G";

    out<<group<<Messagelen<<subIpAddress<<subPortNum<<Messagetype;

    if(Messagetype=="I"||Messagetype=="S")
        out<<curTemp<<ObjTemp<<speed;
    else if(Messagetype=="K")
        out<<num;

    QHostAddress  *hostaddr = new QHostAddress(IpAddress);
    udpSocket_send->writeDatagram(data,*hostaddr,6665);
}

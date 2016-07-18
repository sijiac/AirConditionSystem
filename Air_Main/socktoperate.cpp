#include "socktoperate.h"

SocktOperate::SocktOperate()
{
    udpSocketSend = new QUdpSocket(this);
}
SocktOperate::~SocktOperate(){

}
//void SocktOperate::receive(){
//    qDebug()<<"receive";
//}
//发送刷新频率
void SocktOperate::sendMessage(QString ipAddress,int portNum,int frequency){

    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 2;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("F");//表示信息为刷新频率
    out<<frequency;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送主控机模式,mode "1"表示制冷 "0"表示制热
void SocktOperate::sendMessage(QString ipAddress,int portNum,QString mode){

    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    int messagelen = 2;//之后的变量数量

    out<<QString("G")<<messagelen<<localIpAddress<<localPortNum<<QString("M")<<mode;

    //qDebug()<<ipAddress<<portNum;
    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,*targetAddr,portNum); //6665是主控机的端口号
}
//发送当前时间
void SocktOperate::sendMessage(QString ipAddress,int portNum,QDateTime time){

    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 2;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("T");//表示信息为刷新频率
    out<<time;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    //qDebug()<<"sendData"<<QString("%1").arg(sendData.size());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送时间比例
void SocktOperate::sendMessage(QString ipAddress,int portNum,int timeRate,int nothing){

    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 2;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("R");//表示信息为刷新频率
    out<<timeRate;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送从控机初始化温度
void SocktOperate::sendMessage(QString ipAddress,int portNum,float subInitalState){
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 2;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("I");//表示信息为刷新频率
    out<<subInitalState;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送从控机当前费用
void SocktOperate::sendMessage(QString ipAddress,int portNum,float use,float cost){
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 3;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("L");//表示信息为刷新频率
    out<<use<<cost;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    //qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送回复从控机的空调风信息
void SocktOperate::sendMessage(QString ipAddress,int portNum,QString windSpeed,float temp){
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 3;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("H");//表示信息为刷新频率
    out<<windSpeed<<temp;//当前主控机的刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    // qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}
//发送关机  G
void SocktOperate::sendMessage(QString ipAddress,int portNum){
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out<<QString("G");//组的标号
    int messagelen = 0;//之后的变量数量
    out<<messagelen;
    out<<localIpAddress<<localPortNum;//发送自己的套接字

    out<<QString("G");//表示信息为刷新频率

    QHostAddress  * targetAddr = new QHostAddress(ipAddress);//主控机IP
    // qDebug()<<"sendData"<<QString::fromStdString(sendData.toStdString());
    udpSocketSend->writeDatagram(sendData,* targetAddr,portNum); //6665是主控机的端口号
}

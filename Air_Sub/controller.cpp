#include "controller.h"
#include <qDebug>

Controller::Controller(QObject *parent):QObject(parent){

}
Controller::~Controller(){
    sender->sendmessage(1,"G",0,0,NULL,0);
}
void Controller::setController(const QString &IpAddress,const QString &subIpAddress,const int &subPortNum,const int &roomID){
    qDebug()<<IpAddress<<subIpAddress<<subPortNum<<roomID;
    sub=new SubState();
    sub->setid(roomID);
    sender=new SocketOperate(IpAddress,subIpAddress,subPortNum);
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUp()));
    udpSocket_recv=new QUdpSocket();

    QHostAddress *hostaddr= new QHostAddress(subIpAddress);
    bool  conn = udpSocket_recv->bind(*hostaddr,subPortNum,QUdpSocket::ShareAddress);
    if(!conn){
        qDebug()<<"连接错误";
    }

    connect(udpSocket_recv,SIGNAL(readyRead()),this,SLOT(receive()));

    sender->sendmessage(2,"K",0,0,NULL,roomID);

    sleep(150);
    sender->sendmessage(2,"K",0,0,NULL,roomID);

    sleep(150);
    sender->sendmessage(4,"S",sub->getNewTemp(),sub->getObjectTemp(),sub->getWindRate(),0);
    timer->start(1000);
}

void Controller::timerUp()
{
    if(sub->getinService()&&(
            (sub->getNewTemp()<=sub->getObjectTemp()&&sub->getMode()=="1")||
            (sub->getNewTemp()>=sub->getObjectTemp()&&sub->getMode()=="0")))
    {
        qDebug()<<"发F";
        sender->sendmessage(4,"F",sub->getNewTemp(),sub->getObjectTemp(),sub->getWindRate(),0);
        sub->setinService(false);
    }
    //else if(!sub->getinService()&&fabs(sub->getNewTemp()-sub->getObjectTemp())>1)
    else if(!sub->getinService()&&(
            (sub->getNewTemp()-sub->getObjectTemp()>1&&sub->getMode()=="1")||
            (sub->getObjectTemp()-sub->getNewTemp()>1&&sub->getMode()=="0")))
    {
            qDebug()<<"发S";
            sleep(150);
            sender->sendmessage(4,"S",sub->getNewTemp(),sub->getObjectTemp(),sub->getWindRate(),0);
    }
    else if(!sub->getinService())
    {
           sender->sendmessage(4,"I",sub->getNewTemp(),sub->getObjectTemp(),"0",0);
    }
    else if(sub->getinService()){
           sender->sendmessage(4,"I",sub->getNewTemp(),sub->getObjectTemp(),sub->getWindRate(),0);
    }
    timer->start(sub->getRefreahRate()*1000);
}
void Controller::StartService(float objictTemp,QString Rate)
{
    sub->setWindRate(Rate);
    if(sub->getNewTemp()>objictTemp&&sub->getMode()=="1"||sub->getNewTemp()<objictTemp&sub->getMode()=="0")
    {
        sender->sendmessage(4,"S",sub->getNewTemp(),objictTemp,Rate,0);
        sub->setObjectTemp(objictTemp);
    }
}
void Controller::Close()
{
    sender->sendmessage(1,"G",0,0,NULL,0);
}


SubInfo Controller::getsubInfo()
{
    SubInfo si;
    si.InnerTemp=sub->getNewTemp();
    si.Mode=sub->getMode();
    si.ObjectTemp=sub->getObjectTemp();
    si.RefreshRate=sub->getRefreahRate();
    si.TotalMoney=sub->GetMoney();
    si.Mode=sub->getMode();
    si.time=sub->getcurTime();
    si.useage=sub->getUsage();
    si.windrate=sub->getWindRate();
    return si;
}

void Controller::receive()
{

    QByteArray data;
    while(udpSocket_recv->hasPendingDatagrams())
    {
        data.resize(udpSocket_recv->pendingDatagramSize());
        udpSocket_recv->readDatagram(data.data(),data.size());
    }
    QDataStream in(&data,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_4);

    QString GroupId;
    int MessageLen;
    QString Ip;
    int port;
    QString Messagetype;
    in>>GroupId>>MessageLen>>Ip>>port>>Messagetype;
    qDebug()<<Messagetype;
    if(GroupId=="G")
    {

        if(Messagetype=="F"){
            int rate;
            in>>rate;
            sub->setRefreahRate(rate);
         }else
        if(Messagetype=="M"){
           QString mode;
           in>>mode;
           sub->setMode(mode);
        }else
        if(Messagetype=="T"){

            QDateTime curtime;
            in>>curtime;
            sub->setcurTime(curtime);
        }else
        if(Messagetype=="G")
            {
                qDebug()<<"主机关机啦";
                sub->setinService(false);
            }
       else
      if(Messagetype=="I"){

            float temp;
            in>>temp;
            sub->setObjectTemp(temp);
      }else
     if(Messagetype=="L"){

            float num,cost;
            in>>num>>cost;
            qDebug()<<num<<cost;
            sub->setUsage(num);
            sub->setTotalMoney(cost);
     }else
    if(Messagetype=="H"){

            QString rate;
            float windtemp;
            in>>rate>>windtemp;

            sub->setinService(true);
        }
    }
}
void Controller::sleep(unsigned int ms)
{
    QTime reachTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < reachTime);
}



#include "substate.h"
#include <QDebug>
SubState::SubState()
{
    InnerTemp=25;
    inService=false;
    WindRate="1";
    RefreshRate=1;
    ObjectTemp=0;
    Mode="0";

    timersub=new QTimer();
    connect(timersub,SIGNAL(timeout()),this,SLOT(subtimerUp()));
    timersub->start(1000);
}

void SubState::subtimerUp()
{

    qDebug()<<Mode<<inService<<"==================================";
    curTime=curTime.addSecs(1);

    if(!inService&&Mode=="1")
        InnerTemp+=1.0/60;
    else if(!inService&&Mode=="0")
        InnerTemp-=1.0/60;
    else if(WindRate=="1"&&Mode=="1")
        InnerTemp-=3.0/60;
    else if((Mode=="1"&&InnerTemp>ObjectTemp)||(Mode=="0"&&InnerTemp<ObjectTemp))
    {
    if(WindRate=="1"&&Mode=="0")
        InnerTemp+=3.0/60;
    else if(WindRate=="2"&&Mode=="1")
        InnerTemp-=4.0/60;
    else if(WindRate=="2"&&Mode=="0")
        InnerTemp+=4.0/60;
    else if(WindRate=="3"&&Mode=="1")
        InnerTemp-=5.0/60;
    else if(WindRate=="3"&&Mode=="0")
        InnerTemp+=5.0/60;
    }
}
void SubState::setMode(QString mode)
{
    Mode=mode;
}

void SubState::setRefreahRate(int RRate)
{
    RefreshRate=RRate;
}
void SubState::setTotalMoney(float Money)
{
    TotalMoney=Money;
}

void SubState::setWindRate(QString Wrate)
{
    WindRate=Wrate;
}

void SubState::setcurTime(QDateTime time)
{
    curTime=time;
}
void SubState::setid(int Roomid)
{
    id=Roomid;
}
void SubState::setinService(bool in)
{
    inService=in;
}
void SubState::setObjectTemp(float object)
{
       ObjectTemp=object;
}
float SubState::getNewTemp()
{
   return InnerTemp;
}


void SubState::setUsage(float use)
{
    usage=use;
}

#ifndef REQUEST_H
#define REQUEST_H

#include <QDateTime>

class Request
{
public:
    Request(int idIn,QDateTime timeIn,float innerTempIn,float targetTempIn,QString windRateIn){
        int windSpeed = windRateIn.toInt();
        id = idIn;
        time = timeIn;
        innerTemp = innerTempIn;
        targetTemp = targetTempIn;
        windRate = windSpeed;
    }
    Request(){

    }
    int getId()const{
        return id;
    }
    QDateTime getTime ()const{
        return time;
    }
    float getInnerTemp()const{
        return innerTemp;
    }
    float getTargetTemp()const{
        return targetTemp;
    }
    int getWindRate()const{
        return windRate;
    }
    int getlevel()const
    {
        return level;
    }
    void setlevel(int xx)
    {
        level = xx;
    }
    void setRequest(QDateTime timeIn,float innerTempIn,float targetTempIn,int windRateIn){
        time = timeIn;
        innerTemp = innerTempIn;
        targetTemp = targetTempIn;
        windRate = windRateIn;
    }
private:
    int id;
    QDateTime time;
    float innerTemp;
    float targetTemp;
    int windRate;//请求风速
    int level; // 如果插入时房间号已经存在请求了则保留优先级，否则将优先级设为3
};

#endif // REQUEST_H

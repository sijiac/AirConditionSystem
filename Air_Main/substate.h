#ifndef SUBSTATE_H
#define SUBSTATE_H

#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QVector>
#include <QTime>
#include <QDebug>


// 在子状态类中，除了温度曲线外，其他是private
class SubState
{
public:
    QVector<QPair<QTime, float> > TemChange;
    SubState(){}
    SubState(QString xx,int yy){
        IP = xx;
        portNumber = yy;
        InnerTem = 25.0;
        Tem = 25.0;
        totalMoney = 0;
        WindRate = 1;
        workState = 1;
        openNum = 1;
    }
    ~SubState(){}
    void addTemLine(QTime time,float temp){
        if (TemChange.size() >= 10)
            TemChange.pop_front();
        TemChange.push_back(qMakePair(time,temp));
    }
    QString getTemTime(int num) const{
        if (TemChange.size() <= num) return "";
        return TemChange[num].first.toString();
    }
    QString getTemTem(int num) const{
        if (TemChange.size() <= num) return "";
        return QString("%1").arg(TemChange[num].second);
    }

    QString getIP ()const
    {
        return IP;
    }
    void setIP(QString xx)
    {
        IP = xx;
    }
    int getPortNumber()const
    {
        return portNumber;
    }
    void setPortNumber(int xx)
    {
        portNumber = xx;
    }
    float getInnerTem()const
    {
        return InnerTem;
    }
    void setInnerTem(float xx)
    {
        InnerTem = xx;
    }
    float getTem()const
    {
        return Tem;
    }
    void setTem(float xx)
    {
        Tem = xx;
    }
    float getTotalMoney()const
    {
        return totalMoney;
    }
    void setTotalMoney(float xx)
    {
        totalMoney = xx;
    }
    int getWindRate()const
    {
        return WindRate;
    }
    void setWindRate(int xx)
    {
        WindRate = xx;
    }
    void setWorkState(int xx)//设置从控机的运行状态,1正在工作，2正在待机，3已经关机
    {
        workState = xx;
    }
    int getWorkState()const
    {
        return workState;
    }
    void setRecentTime(QTime time){
        recentTime = time;
    }
    QTime getRecentTime()const{
        return recentTime;
    }
    int getOpenNum()const{
        return openNum;
    }
    void setOpenNum(int xx){
        openNum = xx;
    }

private:
    QString IP;
    int portNumber;
    float InnerTem;
    float Tem;
    float totalMoney;
    int WindRate;
    int workState;//表示从控机的运行状态,1正在工作，2正在待机，3已经关机，4断开连接（非正常）
    QTime recentTime;
    int openNum;//表示记录的开关机次数
};

#endif // SUBSTATE_H

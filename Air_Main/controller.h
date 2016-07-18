#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QDeclarativeView>
#include <QQmlApplicationEngine>
//#include <QDeclarativeContext>
#include <QQmlContext>

#include "socktoperate.h"
#include "requestque.h"
#include "substate.h"
#include "strategy.h"
#include "tools.h"
#include "mangermapper.h"
#include "submodel.h"
#include "diarymodel.h"
//#include "logincontroller.h"


#define localIP "172.27.35.1"


extern QString username;

typedef struct MainAirConditionerState{
    QString mode;//主控机工作模式，"1"表示制冷，"0"表示制热
    int refreshRate;//从控机对主控机发送定时消息的刷新频率
    int timeRate;//系统时间进行的比例
    float subInitalState;//从控机应该把自己初始化的温度
    QDateTime nowTime;//当前系统时间
    int strategyNum;//策略编号，1:先来先服务，2：时间片轮转，3：短作业优先
    float price;//每单位功耗的价格
}MainState;


class Controller:public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    Q_INVOKABLE int getMainState(const QString &queryName);
    Q_INVOKABLE void setMainState(const QString &setName,int data);
    //Q_INVOKABLE bool tryLogin(const QString &id,const QString &password);
    Q_INVOKABLE QString getNowTime(){
        return mainState.nowTime.toString();
    }
    Q_INVOKABLE void trySendMessage();
    Q_INVOKABLE int getH(){
        return mainState.nowTime.time().hour();
    }
    Q_INVOKABLE QString getM(){
        int min =  mainState.nowTime.time().minute();
        if(min < 10){
            return QString("0%1").arg(min);
        }
        return QString("%1").arg(min);
    }
    Q_INVOKABLE int getMonth(){
        return mainState.nowTime.date().month();
    }
    Q_INVOKABLE int getDay(){
        return mainState.nowTime.date().day();
    }
    Q_INVOKABLE int getWeekNum(){
        return mainState.nowTime.date().dayOfWeek();
    }
    Q_INVOKABLE QString getSec(){
        int sec = mainState.nowTime.time().second();
        if(sec < 10){
            return QString("0%1").arg(sec);
        }
        return QString("%1").arg(sec);
    }
    Q_INVOKABLE int getNumOfSub(){
        return SubMap.size();
    }
    Q_INVOKABLE QString getTemTem(int index,int num)const{
        int roomId = ((SubModel*)subModel.value(index))->getRoomId().toInt();
        if(!SubMap.contains(roomId)) return QString("");
        return SubMap.value(roomId).getTemTem(num);
    }
    Q_INVOKABLE QString getTemTime(int index,int num)const{
        int roomId = ((SubModel*)subModel.value(index))->getRoomId().toInt();
        if(!SubMap.contains(roomId)) return QString("");
        else    return SubMap.value(roomId).getTemTime(num);
    }
    // ------ Chart
    Q_INVOKABLE QString chart_getRoomID(int index)const
    {
        if (SubMap.size() <= index) return "";
        QString roomId = ((SubModel*)subModel.value(index))->getRoomId();
        qDebug() << "~~~" << roomId << "~~~~";
        return roomId;
    }
    Q_INVOKABLE QString chart_getMoney_day(int index, int mm, int dd)const
    {
        if (SubMap.size() <= index) return "";
        int roomId = ((SubModel*)subModel.value(index))->getRoomId().toInt();
        float mid = manger->getVoltage(roomId, mm, dd) * 5;
        qDebug() << "~~~" << mid << "~~~~";
        return QString("%0").arg(mid);
    }
    Q_INVOKABLE QString chart_getMoney_month(int index, int mm)const
    {
        if (SubMap.size() <= index) return "";
        int roomId = ((SubModel*)subModel.value(index))->getRoomId().toInt();
        float mid = manger->getVoltage(roomId, mm) * 5;
        qDebug() << "~~~" << mid << "~~~~";
        return QString("%0").arg(mid);
    }
    Q_INVOKABLE QString getLocalIP(){
        return localIpAddress;
    }

    /******返回从控机的状态********
     * value的值选择返回的内容
    1.IP
    2.portNumber
    3.innerTem
    4.tem
    5.totalMoney
    6.windRate
    7.workState
    8.voltage
    9.openNum
    ******/
    Q_INVOKABLE QString getSubState(int index,int value){
        int roomId = ((SubModel*)subModel.value(index))->getRoomId().toInt();
        //qDebug()<<roomId;
        if(!SubMap.contains(roomId)) return QString("");
        if(value == 1){
            return SubMap.value(roomId).getIP();
        }else if(value == 2){
            return QString("%1").arg(SubMap.value(roomId).getPortNumber());
        }else if(value == 3){
            return QString("%1").arg(SubMap.value(roomId).getInnerTem());
        }else if(value == 4){
            return QString("%1").arg(SubMap.value(roomId).getTem());
        }else if(value == 5){
            return QString::number(SubMap.value(roomId).getTotalMoney(),'f',2);
        }else if(value == 6){
            return QString("%1").arg(SubMap.value(roomId).getWindRate());
        }else if(value == 7){
            //表示从控机的运行状态,1正在工作，2正在待机，3已经关机，4断开连接（非正常）
            switch (SubMap.value(roomId).getWorkState()) {
            case 1:
                return QString("正在工作");
            case 2:
                return QString("正在待机");
            case 3:
                return QString("已经关机");
            case 4:
                return QString("断开连接");
            default:
                return QString("");
            }
            return QString("%1").arg(SubMap.value(roomId).getWorkState());
        }else if(value == 8){
            return QString::number(SubMap.value(roomId).getTotalMoney() / 5.0 , 'f', 2);
        }else if(value == 9){
            //qDebug()<<roomId;
            //qDebug()<<SubMap.value(roomId).getOpenNum();
            //qDebug()<<"lzlzlz:"<<QString("%1").arg(SubMap.value(roomId).getOpenNum());
            return QString("%1").arg(SubMap.value(roomId).getOpenNum());
        }
    }

    QList<QObject*> getSubModel(){
        //QList<QObject*> dataList;
//        for(int i = 0;i < subModel.size();i++){
//            subModel.removeFirst();
//        }
        while(!subModel.isEmpty()){
            subModel.removeFirst();
        }
        qDebug()<<"subModel isEmpty:"<<subModel.isEmpty();
        QMapIterator<int, SubState> i(SubMap);
        while(i.hasNext()){
            i.next();
            subModel.append(new SubModel(i.key()));
        }
        //subModel.append(new SubModel(10101));
        return subModel;
    }
    QList<QObject*> getDiaryModel(){
        //tools::get_instance()->recordOperation("Test","Hello World","111",QDateTime::currentDateTime());
        diaryModel = tools::get_instance()->getRecordList();
        //qDebug()<<diaryModel.size();
        return diaryModel;
    }
    QList<QObject*> getRequestQue(){
        while(!requestQueModel.isEmpty()){
            requestQueModel.removeFirst();
        }
        for(int i = 0;i < requestToHandle.size();i++){
            requestQueModel.append(new DiaryModel(QString("%1").arg(requestToHandle[i].getId()),"响应中",
                                                  requestToHandle[i].getTime().toString(),
                                                  QString("室内温度:%1/目标温度:%2/风速:%3")
                                                  .arg(requestToHandle[i].getInnerTemp())
                                                  .arg(requestToHandle[i].getTargetTemp())
                                                  .arg(requestToHandle[i].getWindRate())));
        }
        QMap<int,Request> lastRequest = requestQue.getRequestQue();
        QMapIterator<int, Request> i(lastRequest);
        while (i.hasNext()) {
            i.next();
            bool isServe = false;
            for(int j = 0;j < requestToHandle.size();j++){
                if(i.value().getId() == requestToHandle[j].getId()) isServe = true;
            }
            if(!isServe){
                requestQueModel.append(new DiaryModel(QString("%1").arg(i.key()),"",
                                                      i.value().getTime().toString(),
                                                      QString("室内温度:%1/目标温度:%2/风速:%3")
                                                      .arg(i.value().getInnerTemp())
                                                      .arg(i.value().getTargetTemp())
                                                      .arg(i.value().getWindRate())));
            }
        }
        return requestQueModel;
    }
    void setEngine(QQmlApplicationEngine * xx){
        engine = xx;
    }
private slots:
    void updateDateTime();
    void receive();
    void sendL();
    void getDisConnect();
private:
    void sendResponse(Request request);
    int getID(QString IP,int portNum);//根据网址查询对应房间号
    void sendG();//发送关机帧

    MainState mainState;//主控机状态
    QMap<int, SubState> SubMap; //从控机状态

    RequestQue requestQue;//从控机的请求队列，相当于buffer1
    QVector<Request> requestToHandle;//正在处理中的请求，相当于buffer2
    SocktOperate * socket;//socket发送信息类
    MangerMapper * manger;
    //SubState subState;//从控机的套接字与ID的Map

    QTimer * timer;//定时器，用于按照时间速率刷新时间
    QTimer * timer5s;//5s的定时器，用于定时发送消费信息
    QTimer * timer15s;//15s的定时器，用于判断从控机是否断开连接
    QUdpSocket * udpSocketReceive;//接受信息使用的Socket
    QString localIpAddress = QString(localIP);//主机的IP地址
    int localPortNum = 6665;//主机使用的端口号

    QList<QObject*> diaryModel;
    QList<QObject*> subModel;
    QList<QObject*> requestQueModel;
    QQmlApplicationEngine * engine;//qml的引擎指针
};

#endif // CONTROLLER_H

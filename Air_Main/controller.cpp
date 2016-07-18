 #include "controller.h"

Controller::Controller(QObject *parent):QObject(parent){

    mainState.nowTime = QDateTime::currentDateTime();
    mainState.mode = "0";
    mainState.refreshRate = 1;
    mainState.subInitalState = 30.0;
    mainState.timeRate = 1;
    mainState.strategyNum = 1;
    mainState.price = 5;

    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("select * from MainState"));
    sqlQuery.next();

    qDebug()<<"init mainState";

//    mainState.nowTime = QDateTime::currentDateTime();
//    mainState.mode = sqlQuery.value(0).toString();
//    mainState.refreshRate = sqlQuery.value(1).toInt();
//    mainState.subInitalState = sqlQuery.value(3).toFloat();
//    mainState.timeRate = sqlQuery.value(2).toInt();
//    mainState.strategyNum = sqlQuery.value(4).toInt();
//    mainState.price = sqlQuery.value(5).toDouble();


    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateDateTime()));
    timer->start(1000);

    timer5s = new QTimer();
    connect(timer5s,SIGNAL(timeout()),this,SLOT(sendL()));
    timer5s->start(5000);

    timer15s = new QTimer();
    connect(timer15s,SIGNAL(timeout()),this,SLOT(getDisConnect()));
    timer15s->start(5000);

    socket = new SocktOperate();
    manger = new MangerMapper();
    //qDebug()<<"create socket";

    udpSocketReceive = new QUdpSocket(this);
    QHostAddress *hostaddr = new QHostAddress(localIpAddress);
    int masterPort =localPortNum;
    bool  conn=udpSocketReceive->bind(* hostaddr,masterPort,QUdpSocket::ShareAddress);
        //监听本机上的6665端口，如果有消息到来，就会发送readyRead()信号。
        if(conn){
            qDebug()<<"绑定端口成功";
        }else{
            qDebug()<<"绑定端口失败";
        }
    connect(udpSocketReceive,SIGNAL(readyRead()),this,SLOT(receive()));
}
Controller::~Controller(){
    qDebug()<<"Controller析构函数";
    QSqlQuery sqlQuery;
    qDebug()<<"drop:"<<sqlQuery.exec(QString("drop table MainState"));
    QString sql = QString("create table MainState ("
                          "mode varchar(10),"
                          "refreshRate integer,"
                          "timeRate integer,"
                          "subInitalState double,"
                          "strategyNum integer,"
                          "price double,"
                          "nowtime datetime"
                          ");");
    qDebug()<<"create MainState"<<sqlQuery.exec(sql);
    sql = QString("insert into MainState values ( '%1', %2, %3, %4, %5, %6, '%7')")
            .arg(mainState.mode)
            .arg(mainState.refreshRate)
            .arg(mainState.timeRate)
            .arg(mainState.subInitalState)
            .arg(mainState.strategyNum)
            .arg(mainState.price)
            .arg(mainState.nowTime.toString());
    qDebug()<<sql;
    qDebug()<<"insert MainState:"<<sqlQuery.exec(sql);
    sendG();
}
void sleep(unsigned int msec){
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < reachTime);
}

void Controller::receive(){
    qDebug()<<"received";
    QByteArray receiveData;
    while(udpSocketReceive->hasPendingDatagrams()){
        receiveData.resize(udpSocketReceive->pendingDatagramSize());
        udpSocketReceive->readDatagram(receiveData.data(),receiveData.size());
    }
    QDataStream in(&receiveData,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_4);

    QString group;
    in>>group;
    if(group == "G"){
        int varNum;
        QString IP;
        int portNum;
        QString messageType;
        in>>varNum>>IP>>portNum>>messageType;
        qDebug()<<"%%%%receive:"<<messageType;
        if(messageType == "K"){
            int roomNum;
            in>>roomNum;
            qDebug()<<IP<<portNum<<roomNum;
            if(SubMap.contains(roomNum)){
                SubState sub = SubMap.value(roomNum);
                sub.setWorkState(2);
                sub.setOpenNum(sub.getOpenNum()+1);
                SubMap.insert(roomNum,sub);
                qDebug()<<"$$$$1:"<<SubMap.size()<<roomNum;
            }else{
                //在映射表中插入房间的映射
                SubState sub(IP,portNum);
                SubMap.insert(roomNum,sub);
                qDebug()<<"$$$$2:"<<SubMap.size()<<roomNum;
                //重新设置subModel上下文
                qDebug()<<"set subModel";
                engine->rootContext()->setContextProperty("subModel",QVariant::fromValue(getSubModel()));
            }

            //插入从控机连接成功操作记录
            tools::get_instance()->recordOperation("连接成功",QString("从控机(ID:%1)连接成功").arg(roomNum),username,mainState.nowTime);
            engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));
            //对从控机进行初始化
            //发送刷新频率 F
            socket->sendMessage(IP,portNum,mainState.refreshRate);
            sleep(150);
            //发送主控机的运行模式    M
            socket->sendMessage(IP,portNum,QString("%1").arg(mainState.mode));
            sleep(150);
            //发送主控机的当前时间    T
            socket->sendMessage(IP,portNum,mainState.nowTime);
            sleep(150);
            //发送主控机的时间比例    R
            int nothing;
            socket->sendMessage(IP,portNum,mainState.timeRate,nothing);
            sleep(150);
            //发送从控机的初始目标温度  I
            socket->sendMessage(IP,portNum,mainState.subInitalState);

            sleep(150);
            //发送刷新频率 F
            socket->sendMessage(IP,portNum,mainState.refreshRate);
            sleep(150);
            //发送主控机的运行模式    M
            socket->sendMessage(IP,portNum,QString("%1").arg(mainState.mode));
            sleep(150);
            //发送主控机的当前时间    T
            socket->sendMessage(IP,portNum,mainState.nowTime);
            sleep(150);
            //发送主控机的时间比例    R
            socket->sendMessage(IP,portNum,mainState.timeRate,nothing);
            sleep(150);
            //发送从控机的初始目标温度  I
            socket->sendMessage(IP,portNum,mainState.subInitalState);

            sleep(150);
            //发送刷新频率 F
            socket->sendMessage(IP,portNum,mainState.refreshRate);
            sleep(150);
            //发送主控机的运行模式    M
            socket->sendMessage(IP,portNum,QString("%1").arg(mainState.mode));
            sleep(150);
            //发送主控机的当前时间    T
            socket->sendMessage(IP,portNum,mainState.nowTime);
            sleep(150);
            //发送主控机的时间比例    R
            socket->sendMessage(IP,portNum,mainState.timeRate,nothing);
            sleep(150);
            //发送从控机的初始目标温度  I
            socket->sendMessage(IP,portNum,mainState.subInitalState);

        }else if(messageType == "S"){//如果是S包的话创建或者更新请求
            //qDebug()<<"****:"<<IP<<portNum;

            float innerTemp;
            float targetTemp;
            QString windSpeed;
            in>>innerTemp>>targetTemp>>windSpeed;
            int ID = getID(IP,portNum);//得到房间的ID

            if((innerTemp > targetTemp&&mainState.mode == "0")||(innerTemp < targetTemp&&mainState.mode == "1")){
                return ;
            }
            if(ID > 0){
                //qDebug()<<"&&&&:"<<ID;
                qDebug()<<"&&&&3:"<<SubMap.size();
                SubState sub = SubMap.value(ID);
                sub.addTemLine(mainState.nowTime.time(),innerTemp);
                sub.setWorkState(1);
                sub.setInnerTem(innerTemp);
                sub.setTem(targetTemp);
                sub.setWindRate(windSpeed.toInt());
                SubMap.insert(ID,sub);
                qDebug()<<"&&&&3:"<<SubMap.size()<<ID;

                //把收到的请求加入到缓存队列requestQue，等待处理
                Request * request = new Request(ID,mainState.nowTime,innerTemp,targetTemp,windSpeed);
                requestQue.insertRequest(request);

                //调用策略选择是否进入requestToHandle的请求
                requestToHandle = Strategy_Factory::get_instance()->get_strategy(mainState.strategyNum)->get_order(requestQue.getRequestQue());

                //插入从控机请求开始服务的操作记录
                tools::get_instance()->recordOperation("从控机请求",QString("从控机(ID:%1)请求开始服务").arg(ID),username,mainState.nowTime);
                engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));

                //判断是否在requestToHandle中，如果在的话，回复H
                bool send = false;
                for(int j = 0;!send && j < requestToHandle.size();j++){
                    if(requestToHandle[j].getId() == ID){
                        sendResponse(requestToHandle[j]);
                        send =  true;
                    }
                }
            }
        }else if(messageType == "I"){//如果是正常的刷新帧
            qDebug()<<"%%%%IP:"<<IP<<portNum;
            float innerTemp;
            float targetTemp;
            QString windSpeed;
            in>>innerTemp>>targetTemp>>windSpeed;
            int ID = getID(IP,portNum);//得到房间的ID
            if(ID > 0){
                SubState sub = SubMap.value(ID);
                sub.addTemLine(mainState.nowTime.time(),innerTemp);
                sub.setInnerTem(innerTemp);
                sub.setTem(targetTemp);
                sub.setWindRate(windSpeed.toInt());
                sub.setRecentTime(mainState.nowTime.time());//更新收到的最晚的消息
                SubMap.insert(ID,sub);
                qDebug()<<"&&&&4:"<<SubMap.size()<<ID;

                //判断是否在requestToHandle中，如果在的话，回复H
                bool send = false;
                for(int j = 0;!send && j < requestToHandle.size();j++){
                    if(requestToHandle[j].getId() == ID){
                        sendResponse(requestToHandle[j]);
                        send =  true;
                    }
                }
            }
        }else if(messageType == "F"){//停止服务
            int ID = getID(IP,portNum);
            if(ID > 0){
                SubState sub = SubMap.value(ID);
                sub.setWorkState(2);
                SubMap.insert(ID,sub);
                qDebug()<<"&&&&5:"<<SubMap.size()<<ID;

                //从requestQue和requestToHandle中删除对应的服务请求
                QMap<int,Request> requestMap = requestQue.getRequestQue();
                if(requestMap.contains(ID)){
                    requestMap.remove(ID);
                }
                requestQue.setRequestQue(requestMap);
                bool send = false;
                for(int j = 0;!send && j < requestToHandle.size();j++){
                    if(requestToHandle[j].getId() == ID){
                       requestToHandle.removeAt(j);
                       qDebug()<<"remove request:"<<requestToHandle.size();
                       send = true;
                    }
                }
                //插入从控机请求停止服务的操作记录
                tools::get_instance()->recordOperation("请求停止服务",QString("从控机(ID:%1)请求停止服务").arg(ID),username,mainState.nowTime);
                engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));
            }
        }else if(messageType == "G"){//主动关机
            int ID = getID(IP,portNum);
            if(ID > 0){
                SubState sub = SubMap.value(ID);
                sub.setWorkState(3);
                SubMap.insert(ID,sub);
                qDebug()<<"&&&&6:"<<SubMap.size()<<ID;
                qDebug()<<"从控机状态更改为："<<SubMap.value(ID).getWorkState();

                //从requestQue和requestToHandle中删除对应的服务请求
                QMap<int,Request> requestMap = requestQue.getRequestQue();
                if(requestMap.contains(ID)){
                    requestMap.remove(ID);
                }
                requestQue.setRequestQue(requestMap);
                bool send = false;
                for(int j = 0;!send && j < requestToHandle.size();j++){
                    if(requestToHandle[j].getId() == ID){
                       requestToHandle.removeAt(j);
                       qDebug()<<"remove request:"<<requestToHandle.size();
                       send = true;
                    }
                }

                //插入从控机关机的操作记录
                tools::get_instance()->recordOperation("从控机关机",QString("从控机(ID:%1)已经关机").arg(ID),username,mainState.nowTime);
                engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));
            }
        }else if(messageType == "L"){//查询消费
            int ID = getID(IP,portNum);
            if(ID > 0){
                socket->sendMessage(IP,portNum,manger->getVoltage(ID),manger->getVoltage(ID)*(mainState.price));
                //qDebug()<<"查询话费的金额："<<manger->getVoltage(ID);
            }
        }
    }
}
//typedef struct MainAirConditionerState{
//    char mode;//主控机工作模式，"1"表示制冷，"0"表示制热    1/0              1/0
//    int refreshRate;//从控机对主控机发送定时消息的刷新频率  1/5/10        1..3
//    int timeRate;//系统时间进行的比例                    1/10/50/100/300/500/1000  1..7
//    float subInitalState;//从控机应该把自己初始化的温度    16/18/20/23/26   1..5
//    QTime nowTime;//当前系统时间                         string
//}MainState;
int Controller::getMainState(const QString &queryName){
    if(queryName == "mode"){
        if(mainState.mode == QString('1'))   return 1;
        else    return 0;
    }else if(queryName == "refreshRate"){
        if(mainState.refreshRate == 1)  return 1;
        if(mainState.refreshRate == 5)  return 2;
        if(mainState.refreshRate == 10)  return 3;
    }else if(queryName == "timeRate"){
        if(mainState.timeRate == 1) return 1;
        if(mainState.timeRate == 10) return 2;
        if(mainState.timeRate == 50) return 3;
        if(mainState.timeRate == 100) return 4;
        if(mainState.timeRate == 300) return 5;
        if(mainState.timeRate == 500) return 6;
        if(mainState.timeRate == 1000) return 7;
    }else if(queryName == "subInitalState"){
        if(mainState.subInitalState - 16.0 < 0.1)   return 1;
        if(mainState.subInitalState - 18.0 < 0.1)   return 2;
        if(mainState.subInitalState - 20.0 < 0.1)   return 3;
        if(mainState.subInitalState - 23.0 < 0.1)   return 4;
        if(mainState.subInitalState - 26.0 < 0.1)   return 5;
    }else if(queryName == "strategyNum") return mainState.strategyNum;
    return -1;
}
void Controller::setMainState(const QString &setName,int data){
    qDebug()<<"set:"<<setName<<data;
    QString xx;
    if(setName == "mode"){
        QString change = mainState.mode;
        if(data == 1){
            mainState.mode = '1';
            xx = "制冷";
        }else{
            mainState.mode = '0';
            xx = "制热";
        }
        //发送主控机的运行模式    M
        if(change != mainState.mode){
            mainState.subInitalState = 25.0;
            QMapIterator<int, SubState> i(SubMap);
            while (i.hasNext()) {
                i.next();
                socket->sendMessage(i.value().getIP(),i.value().getPortNumber(),QString("%1").arg(mainState.mode));
                sleep(150);
                socket->sendMessage(i.value().getIP(),i.value().getPortNumber(),mainState.subInitalState);
            }
        }
    }else if(setName == "refreshRate"){
        if(data == 1)   mainState.refreshRate = 1;
        if(data == 5)   mainState.refreshRate = 2;
        if(data == 10)   mainState.refreshRate = 3;
        xx = QString("%1").arg(mainState.refreshRate);
        //发送刷新频率 F
        QMapIterator<int, SubState> i(SubMap);
        while (i.hasNext()) {
            i.next();
            socket->sendMessage(i.value().getIP(),i.value().getPortNumber(),QString("%1").arg(mainState.mode));
        }
    }else if(setName == "timeRate"){
        if(data == 1)   mainState.timeRate = 1;
        if(data == 2)   mainState.timeRate = 10;
        if(data == 3)   mainState.timeRate = 50;
        if(data == 4)   mainState.timeRate = 100;
        if(data == 5)   mainState.timeRate = 300;
        if(data == 6)   mainState.timeRate = 500;
        if(data == 7)   mainState.timeRate = 1000;
        xx = QString("%1").arg(mainState.timeRate);
    }else if(setName == "subInitalState"){
        if(data == 1)   mainState.subInitalState = 16.0;
        if(data == 2)   mainState.subInitalState = 18.0;
        if(data == 3)   mainState.subInitalState = 20.0;
        if(data == 4)   mainState.subInitalState = 23.0;
        if(data == 5)   mainState.subInitalState = 26.0;
        xx = QString("%1").arg(mainState.subInitalState);
    }else if(setName == "strategyNum"){
        mainState.strategyNum = data;
        xx = QString("%1").arg(mainState.strategyNum);
    }
    tools::get_instance()->recordOperation("设置主控机",QString("主控机状态%1设置为：%2").arg(setName).arg(xx),username,mainState.nowTime);
    engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));
}
void Controller::updateDateTime(){
    mainState.nowTime=mainState.nowTime.addSecs(1);
    timer->start(1000);
    engine->rootContext()->setContextProperty("requestModel",QVariant::fromValue(getRequestQue()));
}
void Controller::trySendMessage(){
   // socket->sendMessage("127.0.0.1",6666,"1");
}
void Controller::sendResponse(Request request){
    QString IP = SubMap.value(request.getId()).getIP();
    int portNum = SubMap.value(request.getId()).getPortNumber();
    //qDebug()<<"Wind Speed is:"<<QString("%1").arg(request.getWindRate());

    //发送响应信息帧
    socket->sendMessage(IP,portNum,QString("%1").arg(request.getWindRate()),request.getTargetTemp());

    //计算花费的能耗
    float costVoltage = tools::get_instance()->getVoltage_onceOperate(request.getWindRate(),mainState.refreshRate);

    //qDebug()<<"话费的电量为："<<costVoltage;

   // costVoltage += manger->getVoltage(request.getId(),mainState.nowTime.date().month(),mainState.nowTime.date().day());
    manger->addVoltage(request.getId(),mainState.nowTime.date().month(),mainState.nowTime.date().day(),costVoltage);
    SubState sub = SubMap.value(request.getId());
    sub.setTotalMoney(sub.getTotalMoney()+costVoltage*mainState.price);
    SubMap.insert(request.getId(),sub);
    qDebug()<<"&&&&7:"<<SubMap.size()<<request.getId();

    //插入从控机连接成功操作记录
    int ID = getID(IP,portNum);
    tools::get_instance()->recordOperation("请求日志",QString("ID:%1/目标:%2/风速:%3/用电:%4/花费:%5").arg(ID).arg(request.getTargetTemp()).arg(request.getWindRate()).arg(costVoltage).arg(costVoltage*mainState.price),username,mainState.nowTime);
    engine->rootContext()->setContextProperty("diaryModel",QVariant::fromValue(getDiaryModel()));
}
int Controller::getID(QString IP,int portNum){
    QMapIterator<int,SubState> i(SubMap);
    while (i.hasNext()){
        i.next();
        if(i.value().getIP() == IP && i.value().getPortNumber() == portNum){
           return i.key();
        }
    }
    return -1;
}
void Controller::sendL(){
    QMapIterator<int, SubState> i(SubMap);
    while (i.hasNext()) {
        i.next();
        socket->sendMessage(i.value().getIP(),i.value().getPortNumber(),manger->getVoltage(i.key()),manger->getVoltage(i.key())*(mainState.price));
    }
}
void Controller::sendG(){
    QMapIterator<int, SubState> i(SubMap);
    while (i.hasNext()) {
        i.next();
        socket->sendMessage(i.value().getIP(),i.value().getPortNumber());
        sleep(150);
    }
}
void Controller::getDisConnect(){
    QMapIterator<int, SubState> i(SubMap);
    while (i.hasNext()) {
        i.next();
        if(mainState.nowTime.time().operator >=(i.value().getRecentTime().addSecs(15))){
            SubState sub = i.value();
            sub.setWorkState(4);
            SubMap.insert(i.key(),i.value());
        }
    }
	timer15s->start(5000);
}

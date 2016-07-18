#include "mangermapper.h"

MangerMapper::MangerMapper(QObject *parent):QObject(parent){
    query = new QSqlQuery();
    QSqlQuery sql;
    qDebug()<<"create result:"<<query->exec("create table MangerMapper(id varchar(100),idpassword varchar(100),primary key (id))");
    qDebug()<<"the result of insert Manger:"<<insertManger(QString("123"),QString("321"));

    //  日志表
    //qDebug()<<"select"<<sql.exec("select * from Record");
    qDebug()<<"drop Record:"<<sql.exec("drop table Record");
    qDebug()<<"create Record:"<<sql.exec("CREATE TABLE Record ("
                                           "id  INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "kind                VARCHAR(100),"
                                           "content            VARCHAR(100),"
                                           "username           varchar(100),"
                                           "time               DATETIME  );");
    qDebug()<<"insert into Record"<<sql.exec(QString("insert into Record values(0,'1', 'Test', 'Welcome everyone!', datetime())"));
    //qDebug()<<"select chart:"<<sql.exec("select * from chart");
    //qDebug()<<"drop chart:"<<sql.exec("drop table chart");
    qDebug()<<"create chart:"<<sql.exec("create table chart"
                                         "(roomID integer,"
                                             "mm integer,"
                                             "dd integer,"
                                             "voltage float,"
                                             "primary key (roomID,mm,dd))");
}
MangerMapper::~MangerMapper(){

}
bool MangerMapper::insertManger(QString id, QString password){
    QString sqlString=QString("insert into MangerMapper values ("+id+","+password+")");
    qDebug()<<sqlString;
    return query->exec(sqlString);
}
bool MangerMapper::judgePassword(QString id, QString password){
    QString sqlString=QString("select idpassword from MangerMapper where id = "+id);
    qDebug()<<sqlString;
    //qDebug()<<password;
    query->exec(sqlString);
    if(query->next())
    {
        //qDebug()<<"true";
        return query->value(0) == password;
    }
    return false;
}

void MangerMapper::setVoltage(int RoomId,int mm,int dd, float voltage)
{
    qDebug()<<"setVoltage:"<<RoomId<<mm<<dd<<voltage;
    QSqlQuery sql;
    sql.exec(QString("select voltage from chart where roomID = %1 and mm = %2 and dd = %3").arg(RoomId).arg(mm).arg(dd));
    if(sql.next()){
        // qDebug()<<"voltage:"<<sql.value(0);
        qDebug()<<"update chart:"<<sql.exec(QString("update chart set voltage = %1 where roomID = %2 and mm = %3 and dd = %4").arg(voltage).arg(RoomId).arg(mm).arg(dd));
    }else{
        QString sqlString = QString("insert into chart values(%1,%2,%3,%4)").arg(RoomId).arg(mm).arg(dd).arg(voltage);
        // qDebug()<<sqlString;
        qDebug()<<"insert chart:"<<sql.exec(sqlString);
    }
}
//void setTotalMoney(int RoomId, float money)
//{

//}

float MangerMapper::getVoltage(int RoomId, int mm)
{
    QSqlQuery sql;
    QString sqlString=QString("select voltage from chart where roomID = %1 and mm = %2").arg(RoomId).arg(mm);
    qDebug()<<sqlString;
    sql.exec(sqlString);
    float voltage = 0;
    while(sql.next()){
        qDebug() <<sql.value(0).toFloat();
        voltage += sql.value(0).toFloat();
    }
    qDebug() <<voltage;
    return voltage;
}
float MangerMapper::getVoltage(int RoomId, int mm, int dd)
{
    QSqlQuery sql;
    QString sqlString=QString("select voltage from chart where roomID = %1 and mm = %2 and dd = %3").arg(RoomId).arg(mm).arg(dd);
    qDebug()<<sqlString;
    sql.exec(sqlString);
    if(sql.next())
        return sql.value(0).toFloat();
    else
        return 0;
}
void MangerMapper::addVoltage(int RoomId, int mm, int dd,float voltage){
    float former = getVoltage(RoomId,mm,dd);
    setVoltage(RoomId,mm,dd,voltage+former);
}
float MangerMapper::getVoltage(int RoomId){
    QSqlQuery sql;
    QString sqlString=QString("select voltage from chart where roomID = %1").arg(RoomId);
    qDebug()<<sqlString;
    sql.exec(sqlString);
    float voltage = 0;
    while(sql.next()){
        voltage += sql.value(0).toFloat();
    }
    return voltage;
}

//float getTotalmoney(int RoomId, int mm)
//{

//}
//float getTotalmoney(int RoomId, int mm, int dd)
//{

//}

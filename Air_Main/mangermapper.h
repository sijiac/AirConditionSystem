#ifndef MANGERMAPPER_H
#define MANGERMAPPER_H

#include <QObject>
#include <QDebug>
#include "database.h"

class MangerMapper:public QObject
{
    Q_OBJECT
public:
    explicit MangerMapper(QObject *parent = 0);
    ~MangerMapper();

    bool insertManger(QString id,QString password);
    bool judgePassword(QString id,QString password);
    void setVoltage(int RoomId,int mm,int dd, float voltage);
    float getVoltage(int RoomId);
    float getVoltage(int RoomId, int mm);
    float getVoltage(int RoomId, int mm, int dd);
    void addVoltage(int RoomId, int mm, int dd,float voltage);
public slots:
    void refresh(){
        qDebug()<<"Called the C++ slot";
    }
private:
    QSqlQuery * query;
};

#endif // MANGERMAPPER_H

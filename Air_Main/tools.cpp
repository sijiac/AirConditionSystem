
#include "tools.h"

#include <QDebug>

tools* tools :: single = NULL;

float tools ::getPrice_onceOperate(float Tem, float InnerTem, int WindRate, int ti)
{
     float voltage = getVoltage_onceOperate(WindRate, ti);
     float cost = voltage * 5;
     return cost;
}
float tools ::getVoltage_onceOperate(int WindRate, int second)
{
    float discount;
    if(WindRate == 1) discount = 0.8;
    else if(WindRate == 2) discount = 1;
    else if(WindRate == 3) discount = 1.3;
    else discount = 0;
    return discount*float(second)/60.0;
}
bool tools ::recordOperation(QString kind, QString content, QString username, QDateTime ti)
{
    QString sql = QString("insert into Record values(null, '%1',  '%2', '%3', '%4');").arg(kind).arg(content).arg(username).arg(ti.toString());
    QSqlQuery query;
    qDebug()<<"Record"<<sql;
    return query.exec(sql);
}
QList<QObject*> tools::getRecordList()
{
    QList<QObject*> dataList;
    QString sql = QString("select * from Record;");
    QSqlQuery query;
    query.exec(sql);
    while(query.next()){
        dataList.append(new DiaryModel(query.value(1).toString(),query.value(3).toString(),query.value(2).toString(),query.value(4).toString()));
    }
    return dataList;
}





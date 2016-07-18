#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QTime>
#include <QDate>
#include "database.h"
#include "diarymodel.h"

class tools
{

private:
    static tools* single;

public:
    static tools* get_instance()
    {
        if (single == NULL)
        {
            single = new tools();
        }
        return single;
    }
    float getPrice_onceOperate(float  Tem, float InnerTem, int WindRate, int ti);
    float getVoltage_onceOperate(int WindRate, int ti);
    bool recordOperation(QString kind, QString content, QString username, QDateTime ti);
    QList<QObject*> getRecordList();
};

#endif // TOOLS_H

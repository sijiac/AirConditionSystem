#ifndef SUBSTATE_H
#define SUBSTATE_H
#include <QString>
#include <Qtime>
#include <qtimer.h>
struct SubInfo
{
    float     InnerTemp;
    float     ObjectTemp;
    int       RefreshRate;
    float     TotalMoney;
    QString   Mode;
    QDateTime time;
    float     useage;
    QString  windrate;
};

class SubState:QObject
{
    Q_OBJECT
private:
    int id;

    QString   IpAddress;
    int       port;
    float     InnerTemp;
    float     ObjectTemp;
    int       RefreshRate;
    float     Temp;
    QString   Mode;
    float     TotalMoney;
    QString   WindRate;
    QDateTime curTime;
    bool      inService;
    QTimer   *timersub;
    float usage;
public:
    bool getinService(){return inService;}
    SubState();
    float  getNewTemp();
    int getID(){return id;}
    void  getid();
    float getUsage(){return usage;}
    float getObjectTemp(){return ObjectTemp;}
    QString getWindRate(){return WindRate;}
    int getRefreahRate(){return RefreshRate;}
    QString getMode(){return Mode;}
    float GetMoney(){return TotalMoney;}
    QDateTime getcurTime(){return curTime;}

      void setRefreahRate(int  RRate);
      void setTotalMoney(float Money);
      void setWindRate(QString WRate);
      void setcurTime(QDateTime time);
      void setid(int Roomid);
      void setinService(bool in);
      void setObjectTemp(float object);
      void setMode(QString mode);
      void setUsage(float use);

private slots:
    void subtimerUp();
};

#endif // SUBSTATE_H

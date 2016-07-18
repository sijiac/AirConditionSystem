#ifndef STRATEGY_H
#define STRATEGY_H

#include <QMap>
#include <QVector>
#include "request.h"
#include <QtAlgorithms>

class Strategy
{
protected:
    const static int num = 3; // 每次弹出的请求数量
public:
    virtual QVector<Request> get_order(QMap<int,Request> requestMap)
    {
        QVector<Request> res;
        return res;
    }
};

class FirstIn_Server : public Strategy
{
public:
   QVector<Request> get_order(QMap<int,Request> requestMap);
};

class Splice_Turn : public Strategy
{
private:
    int cnt[100];
public:
    QVector<Request> get_order(QMap<int, Request> requestMap);
    Splice_Turn()
    {
        for (int i = 0; i < 100; i++) cnt[i] = 0;
    }
};

class Shortest_First: public Strategy
{

public:
    QVector<Request> get_order(QMap<int, Request> requestMap);
};

class Strategy_Factory
{
private:
    QMap<int, Strategy*> strategy_catalog;
    static Strategy_Factory* single;
public:
    //析构函数
    ~Strategy_Factory()
    {
    }
    //构造函数
    Strategy_Factory()
    {
        strategy_catalog.clear();
        strategy_catalog.insert(1, new FirstIn_Server());
        strategy_catalog.insert(2, new Splice_Turn());
        strategy_catalog.insert(3, new Shortest_First());
    }
    static Strategy_Factory* get_instance()
    {
        if (single == NULL)
        {
            single = new Strategy_Factory();
        }
        return single;
    }
    Strategy* get_strategy(int id)
    {
        return strategy_catalog.find(id).value();
    }
};

#endif // STRATEGY_H

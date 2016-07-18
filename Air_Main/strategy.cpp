#include "strategy.h"

Strategy_Factory* Strategy_Factory::single = NULL;
bool cmpA(Request A, Request B)
{
    if (A.getTime() < B.getTime()) return true;
    else return false;
}

bool cmpB(Request A, Request B)
{
    float timeA = (A.getInnerTemp() - A.getTargetTemp()) / A.getWindRate();
    float timeB = (B.getInnerTemp() - B.getTargetTemp()) / B.getWindRate();
    if (timeA < timeB) return true;
    else return false;
}

bool cmpC(Request A, Request B)
{
    if (A.getlevel() > B.getlevel())
        return true;
    else if (A.getlevel() == B.getlevel())
        return cmpA(A,B);
    else
        return false;
}

QVector<Request> FirstIn_Server::get_order(QMap<int, Request> requestMap)
{
    QVector<Request> res;
    for (QMap<int,Request>::iterator ite = requestMap.begin(); ite != requestMap.end(); ++ite)
    {
            res.push_back(ite.value());
    }
    qSort(res.begin(), res.end(), cmpA);
    while(res.size() > num)
    {
        res.pop_back();
    }
//    for (int i = 0; i < res.size(); i++)
//    {
//        requestMap.erase(requestMap.find(res[i].getId()));
//    }
    return res;
}

QVector<Request> Splice_Turn::get_order(QMap<int, Request> requestMap)
{
    QVector<Request> res;
    for (QMap<int,Request>::iterator ite = requestMap.begin(); ite != requestMap.end(); ++ite)
    {
            if (ite.value().getlevel()<3) ite.value().setlevel(ite.value().getlevel() + 1);
            res.push_back(ite.value());
    }
    qSort(res.begin(), res.end(), cmpA);
    while(res.size() > num)
    {
        res.pop_back();
    }
    return res;
}

QVector<Request> Shortest_First::get_order(QMap<int, Request> requestMap)
{
    QVector<Request> res;
    for (QMap<int,Request>::iterator ite = requestMap.begin(); ite != requestMap.end(); ++ite)
    {
            res.push_back(ite.value());
    }
    qSort(res.begin(), res.end(), cmpB);
    while(res.size() > num)
    {
        res.pop_back();
    }
    return res;
}

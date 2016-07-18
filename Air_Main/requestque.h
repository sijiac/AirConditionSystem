#ifndef REQUESTQUE_H
#define REQUESTQUE_H

#include <QMap>
#include "request.h"

class RequestQue
{
public:
    RequestQue();
    void insertRequest(Request * requestIn){
        requestMap.insert(requestIn->getId(),*requestIn);
    }
    QMap<int,Request> getRequestQue(){
        return requestMap;
    }
    void setRequestQue(QMap<int,Request>  requestMapIn){
        requestMap = requestMapIn;
    }

private:
    QMap<int,Request> requestMap;
};

#endif // REQUESTQUE_H

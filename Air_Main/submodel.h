#ifndef SUBMODEL_H
#define SUBMODEL_H

#include <QObject>
#include <QString>

class SubModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomId READ getRoomId WRITE setRoomId NOTIFY roomIdChanged)
public:
    SubModel();
    SubModel(int xx){
        roomId = xx;
    }
    QString getRoomId()const{
        return QString("%1").arg(roomId);
    }
    void setRoomId(const QString &xx){
        roomId = xx.toInt();
    }
signals:
    void roomIdChanged();
private:
    int roomId;
};

#endif // SUBMODEL_H

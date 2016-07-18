#ifndef DIARYMODEL_H
#define DIARYMODEL_H

#include <QObject>
#include <QString>

class DiaryModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Type READ getType WRITE setType NOTIFY TypeChanged)
    Q_PROPERTY(QString User READ getUser WRITE setUser NOTIFY UserChanged)
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)
    Q_PROPERTY(QString Content READ getContent WRITE setContent NOTIFY ContentChanged)
public:
    DiaryModel();
    DiaryModel(QString type,QString user,QString time,QString content){
        Type = type;
        User = user;
        Time = time;
        Content = content;
    }
    QString getType()const{
        return Type;
    }
    QString getUser()const{
        return User;
    }
    QString getTime()const{
        return Time;
    }
    QString getContent()const{
        return Content;
    }
    void setType(const QString xx){
        Type = xx;
    }
    void setUser(const QString xx){
        User = xx;
    }
    void setTime(const QString xx){
        Time = xx;
    }
    void setContent(const QString xx){
        Content = xx;
    }
signals:
    void TypeChanged();
    void UserChanged();
    void TimeChanged();
    void ContentChanged();
private:
    QString Type;
    QString User;
    QString Time;
    QString Content;
};

#endif // DIARYMODEL_H

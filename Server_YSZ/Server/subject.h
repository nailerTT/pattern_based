#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QString>
#include "QList"
#include <QMap>

class Observer;
class Subject : public QObject
{
    Q_OBJECT
public:
    explicit Subject();
    ~Subject(){}
    virtual void NotiFy(QMap<QString,QString> map);
    void RemoveObserer(Observer* observer);
signals:
protected:
    void AddObserver(Observer* ob);
private:
    QList<Observer*> _observers;
};

#endif // SUBJECT_H

#include "subject.h"
#include "observer.h"
#include "QDebug"
Subject::Subject()
    : QObject(nullptr)
{

}

void Subject::NotiFy(QMap<QString, QString> map)
{
    for(auto it = this->_observers.begin();it!=this->_observers.end();it++)
        (*it)->Update(map);
}

void Subject::RemoveObserer(Observer *observer)
{
    int idx = -1;
    qDebug()<<this->_observers.size();

    for(int i=0;i<this->_observers.size();i++)
    {
        if(this->_observers[i] == observer)
        {
            idx = i;
            break;
        }
    }
    if(idx > 0)
    {
        this->_observers.removeAt(idx);
    }
}

void Subject::AddObserver(Observer *ob)
{
    this->_observers.append(ob);
}

#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>
#include <QMap>
#include <QString>
class Subject;
class Observer : public QObject
{
    Q_OBJECT
public:
    virtual ~Observer()=0;
    explicit Observer(Subject* subject = nullptr);
    virtual bool Update(const QMap<QString,QString>& map) = 0;
signals:
private:
    Subject* _subject;
};

#endif // OBSERVER_H

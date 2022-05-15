#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QList>
class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref) = 0;
    virtual bool ADD(const QList<QString>& values,QString&ref) = 0;
    virtual bool Del(const QList<QString>& id) = 0;
    virtual bool Update(const QList<QString>& id,const QPair<QString,QString> field_value) = 0;
    static unsigned int GetANewId();
signals:
private:
    static unsigned int id;
    friend class HandlerFactory;
protected:
    virtual ~Handler(){}
};

#endif // HANDLER_H

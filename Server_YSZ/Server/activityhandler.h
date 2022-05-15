#ifndef ACTIVITYHANDLER_H
#define ACTIVITYHANDLER_H

#include "handler.h"
#include "activitysystem.h"

class AcitivityHandler : public Handler
{
    Q_OBJECT
public:
    AcitivityHandler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref);
    virtual bool ADD(const QList<QString>& values,QString&ref);
    virtual bool Del(const QList<QString>& id);
    virtual bool Update(const QList<QString>& id,const QPair<QString,QString> field_value);
private:
    ActivitySystem as;
};

#endif // ACTIVITYHANDLER_H

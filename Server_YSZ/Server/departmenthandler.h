#ifndef DEPARTMENTHANDLER_H
#define DEPARTMENTHANDLER_H

#include "handler.h"
#include "departmentinfomanager.h"
class DepartmentHandler : public Handler
{
    Q_OBJECT
public:
    DepartmentHandler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref);
    virtual bool ADD(const QList<QString>& values,QString&ref);
    virtual bool Del(const QList<QString>& id);
    virtual bool Update(const QList<QString>& id,const QPair<QString,QString> field_value);
private:
    DepartmentInfoManager dim;
};

#endif // DEPARTMENTHANDLER_H

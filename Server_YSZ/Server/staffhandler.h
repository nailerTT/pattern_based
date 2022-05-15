#ifndef STAFFHANDLER_H
#define STAFFHANDLER_H

#include "handler.h"
#include "coursesystem.h"
#include "lettersystem.h"
#include "activitysystem.h"
class StaffHandler : public Handler
{
    Q_OBJECT
public:
    StaffHandler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref);
    virtual bool ADD(const QList<QString>& values,QString&ref);
    virtual bool Del(const QList<QString>& id);
    virtual bool Update(const QList<QString>& id, const QPair<QString,QString> field_value);
private:
    CourseSystem cs;
    StaffInfoManager sif;
    LetterSystem ls;
    ActivitySystem as;
};

#endif // STAFFHANDLER_H

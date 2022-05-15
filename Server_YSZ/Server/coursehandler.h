#ifndef COURSEHANDLER_H
#define COURSEHANDLER_H

#include "handler.h"
#include "coursesystem.h"
class CourseHandler : public Handler
{
    Q_OBJECT
public:
    CourseHandler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref);
    virtual bool ADD(const QList<QString>& values,QString&ref);
    virtual bool Del(const QList<QString>& id);
    virtual bool Update(const QList<QString>& id,const QPair<QString,QString> field_value);
private:
    CourseSystem cs;
};

#endif // COURSEHANDLER_H

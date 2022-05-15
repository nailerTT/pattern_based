#ifndef ADDVISITOR_H
#define ADDVISITOR_H

#include "visitor.h"
#include "QString"
#include "QStringList"
class AddVisitor : public Visitor
{
    Q_OBJECT
public:
    explicit AddVisitor(QObject *parent = nullptr);
    virtual bool QueryLetter(const QString& query);
    virtual bool QueryStaff(const QString& query);
    virtual bool QueryCourse(const QString& query);
    virtual bool QueryActivity(const QString& query);
    virtual bool QueryDepartment(const QString& query);
};

#endif // ADDVISITOR_H

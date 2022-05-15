#ifndef DELVISITOR_H
#define DELVISITOR_H

#include "visitor.h"

class DelVisitor : public Visitor
{
    Q_OBJECT
public:
    explicit DelVisitor(QObject *parent = nullptr);
    virtual bool QueryLetter(const QString& query);
    virtual bool QueryStaff(const QString& query);
    virtual bool QueryCourse(const QString& query);
    virtual bool QueryActivity(const QString& query);
    virtual bool QueryDepartment(const QString& query);
};

#endif // DELVISITOR_H

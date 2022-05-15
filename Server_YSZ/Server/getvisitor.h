#ifndef GETVISITOR_H
#define GETVISITOR_H

#include "visitor.h"

class GetVisitor : public Visitor
{
    Q_OBJECT
public:
    explicit GetVisitor(QObject *parent = nullptr);
    virtual bool QueryLetter(const QString& query);
    virtual bool QueryStaff(const QString& query);
    virtual bool QueryCourse(const QString& query);
    virtual bool QueryActivity(const QString& query);
    virtual bool QueryDepartment(const QString& query);
private:
    bool Get(QList<QString> queries, QString table);
};

#endif // GETVISITOR_H

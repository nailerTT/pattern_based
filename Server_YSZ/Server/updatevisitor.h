#ifndef UPDATEVISITOR_H
#define UPDATEVISITOR_H

#include "visitor.h"

class UpdateVisitor : public Visitor
{
    Q_OBJECT
public:
    explicit UpdateVisitor(QObject *parent = nullptr);
    virtual bool QueryLetter(const QString& query);
    virtual bool QueryStaff(const QString& query);
    virtual bool QueryCourse(const QString& query);
    virtual bool QueryActivity(const QString& query);
    virtual bool QueryDepartment(const QString& query);
private:
    bool Update(QList<QString>& queries, const QString table);
};

#endif // UPDATEVISITOR_H

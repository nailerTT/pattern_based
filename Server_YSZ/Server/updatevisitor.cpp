#include "updatevisitor.h"
#include "handlerfactory.h"
UpdateVisitor::UpdateVisitor(QObject *parent)
    : Visitor{parent}
{

}

bool UpdateVisitor::QueryLetter(const QString &query)
{
//id,Update,letter,state,value
    QList<QString> queries = get_queries(query);
    return Update(queries,"letter");
}

bool UpdateVisitor::QueryStaff(const QString &query)
{
    //id,Update,staff,password/name/departmentid/state,value
    QList<QString> queries = get_queries(query);
    return Update(queries,"staff");
}

bool UpdateVisitor::QueryCourse(const QString &query)
{
    //id,Update,course,departmentid/name/description/isMandatory/isComposite,value
    QList<QString> queries = get_queries(query);
    return Update(queries,"course");
}

bool UpdateVisitor::QueryActivity(const QString &query)
{
    //id,Update,activity,time/location/link/name,value
    QList<QString> queries = get_queries(query);
    return Update(queries,"activity");
}

bool UpdateVisitor::QueryDepartment(const QString &query)
{
    //id,Update,department,name,value
    QList<QString> queries = get_queries(query);
    return Update(queries,"department");
}


bool UpdateVisitor::Update(QList<QString> &queries,const QString table)
{
    if(queries.size()!=5)
        return false;
    else if(queries.at(1)!="Update")
        return false;
    else if(queries.at(2)!=table)
        return false;
    HandlerType type;
    if(table == "staff")
    {
        type = HandlerType::Staff;
    }
    else if(table == "activity")
    {
        type = HandlerType::Activity;
    }
    else if(table == "letter")
    {
        type = HandlerType::Letter;
    }
    else if(table == "department")
    {
        type = HandlerType::Department;
    }
    else if(table == "course")
    {
        type = HandlerType::Course;
    }
    else
        return false;
    return HandlerFactory::GetHandler(type)->Update({queries.at(0)},{queries.at(3),queries.at(4)});
}

#include "getvisitor.h"
#include "handlerfactory.h"
GetVisitor::GetVisitor(QObject *parent)
    : Visitor{parent}
{

}

bool GetVisitor::QueryLetter(const QString &query)
{
    //id,Get,letter,password
    QList<QString> queries = get_queries(query);
    return Get(queries,"letter");
}

bool GetVisitor::QueryStaff(const QString &query)
{
    //id,Get,staff,password
    QList<QString> queries = get_queries(query);
    return Get(queries,"staff");
}

bool GetVisitor::QueryCourse(const QString &query)
{
//id,Get,course,all/name/departmentid/decription/isMandatory/isComposite/compositeCourses
    QList<QString> queries = get_queries(query);
    return Get(queries,"course");
}

bool GetVisitor::QueryActivity(const QString &query)
{
    //id,Get,activity,name/time/location/link
    QList<QString> queries = get_queries(query);
    return Get(queries,"activity");
}

bool GetVisitor::QueryDepartment(const QString &query)
{
    //Get,department,departmentid,departmentname
    //Get,department,departmentname,departmentid
    QList<QString> queries = get_queries(query);
    if(queries.size()!=4)
        return false;
    else if(queries[0]!="Get")
        return false;
    QString res;
    if(HandlerFactory::GetHandler(HandlerType::Department)->Get({queries[0]},queries.at(3),res))
    {
        SetResult(res);
    }
    else
        return false;
}

bool GetVisitor::Get(QList<QString> queries, QString table)
{
    if(queries.size()!=4)
        return false;
    else if(queries[1]!="Get")
        return false;
    else if(queries[2]!=table)
        return false;
    HandlerType type;
    if(table == "staff")
        type = HandlerType::Staff;
    else if(table == "letter")
        type = HandlerType::Letter;
    else if(table == "department")
        type = HandlerType::Department;
    else if(table == "course")
        type = HandlerType::Course;
    else if(table == "activity")
        type = HandlerType::Activity;
    QString res;

    if(HandlerFactory::GetHandler(type)->Get({queries[0]},queries.at(3),res))
    {
        SetResult(res);
    }
    else
        return false;
}

#include "delvisitor.h"
#include "handlerfactory.h"
DelVisitor::DelVisitor(QObject *parent)
    : Visitor{parent}
{

}

bool DelVisitor::QueryLetter(const QString &query)
{
// Del,sentletter,letterid,senderid
// Del,receivedletter,letterid,receiverid
    QList<QString> queries = get_queries(query);
    if(queries.size()!=4)
    {
        return false;
    }
    else if(queries.at(0)!="Del")
        return false;
    unsigned int letterid = queries.at(2).toUInt();
    unsigned int staffid = queries.at(3).toUInt();
    queries.removeAt(0);
    queries.removeAt(1);
    if(queries.at(1)=="sentletter")
    {
        queries.insert(0,"send");
    }
    else if(queries.at(1)=="receivedletter")
    {
        queries.insert(0,"receive");
    }
    return HandlerFactory::GetHandler(HandlerType::Letter)->Del(queries);
}

bool DelVisitor::QueryStaff(const QString &query)
{
    //Del,staff,staffid
    QList<QString> queries = get_queries(query);
    if(queries.size()!=3)
        return false;
    else if(queries.at(0)!="Del")
        return false;
    else if(queries.at(1)!="staff")
        return false;

    queries.remove(0,2);
    return HandlerFactory::GetHandler(HandlerType::Staff)->Del(queries);
}

bool DelVisitor::QueryCourse(const QString &query)
{
    QList<QString> queries = get_queries(query);
    if(queries.size()!=3)
        return false;
    return HandlerFactory::GetHandler(HandlerType::Course)->Del(queries);

}

bool DelVisitor::QueryActivity(const QString &query)
{
    QList<QString> queries = get_queries(query);
    //{Del,activity,activityid}
    //{QuitActivity,activityid,staffid}
    if(queries.size()!=3)
        return false;
    return HandlerFactory::GetHandler(HandlerType::Activity)->Del(queries);
}

bool DelVisitor::QueryDepartment(const QString &query)
{
//Del,department,departmentid
    QList<QString> queries = get_queries(query);
    if(queries.size()!=3)
        return false;
    queries.remove(0,2);
    return HandlerFactory::GetHandler(HandlerType::Department)->Del(queries);
}

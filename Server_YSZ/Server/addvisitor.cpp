#include "addvisitor.h"
#include "handlerfactory.h"
AddVisitor::AddVisitor(QObject *parent)
    : Visitor{parent}
{

}

bool AddVisitor::QueryLetter(const QString &query)
{
    //Send,letter, senderid,receiverid,content,title,date
    QString ref;
    QList<QString> queries = get_queries(query);
    if(queries.size()!=7)
        return false;
    else{
        if(queries.at(0)!="Send")
            return false;
        if(queries.at(1)!="letter")
            return false;
    }
    queries.removeAt(0);
    queries.removeAt(1);
    return HandlerFactory::GetHandler(HandlerType::Letter)->ADD(queries,ref);
}

bool AddVisitor::QueryStaff(const QString &query)
{
    //Add,staff,name,state,departmentid,role,gender,password
    QString ref;
    QList<QString> queries = get_queries(query);
    if(queries.size()!=8)
        return false;
    else{
        if(queries.at(0)!="Add")
            return false;
        if(queries.at(1)!="staff")
            return false;
    }
    queries.remove(0,2);
    return HandlerFactory::GetHandler(HandlerType::Staff)->ADD(queries,ref);
}

bool AddVisitor::QueryCourse(const QString &query)
{

    QString ref;
    QList<QString> queries = get_queries(query);
    //Add,course,name,departmentid,description,ismandatory,iscomposite,composite_courses,lecturer
    if(queries.size()==9){
        if(queries.at(0)!="Add")
            return false;
        if(queries.at(1)!="course")
            return false;
        queries.remove(0,2);
        return HandlerFactory::GetHandler(HandlerType::Course)->ADD(queries,ref);
    }
    //Enroll,courseid,staffid
    else if(queries.size()==3)
    {
        if(queries.at(0)!="Enroll")
            return false;
        queries.removeAt(0);
        return HandlerFactory::GetHandler(HandlerType::Course)->ADD(queries,ref);
    }
}

bool AddVisitor::QueryActivity(const QString &query)
{
    QString ref;
    QList<QString> queries = get_queries(query);
    //Add,activity,name,time,location,link
    if(queries.size()==6){
        if(queries.at(0)!="Add")
            return false;
        if(queries.at(1)!="activity")
            return false;
        queries.remove(0,2);
        return HandlerFactory::GetHandler(HandlerType::Activity)->ADD(queries,ref);
    }
    //Join,activityid,staffid,role
    else if(queries.size() == 4)
    {
        if(queries.at(0)!="Join")
            return false;
        queries.removeAt(0);
        return HandlerFactory::GetHandler(HandlerType::Activity)->ADD(queries,ref);
    }
    else
        return false;
}

bool AddVisitor::QueryDepartment(const QString &query)
{
    QString ref;
    QList<QString> queries = get_queries(query);
    //Add,department,name
    if(queries.size()==3)
    {
        if(queries[0]!="Add")
            return false;
        else if(queries[1]!="department")
            return false;
        queries.remove(0,2);
        return HandlerFactory::GetHandler(HandlerType::Department)->ADD(queries,ref);
    }
    else return false;
}


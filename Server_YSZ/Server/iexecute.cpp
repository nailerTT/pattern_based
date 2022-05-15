#include "iexecute.h"
#include "addvisitor.h"
#include "getvisitor.h"
#include "updatevisitor.h"
#include "delvisitor.h"
Execute::Execute(QObject *parent)
    : QObject{parent}
{

}

Execute::~Execute()
{

}

QString Execute::execute(QString query)
{
    Visitor* visitor = nullptr;
    QStringList strlist = query.split(",");
    if(strlist.size() < 3)
        return "fail";
    QString ans;
    if(strlist[0] == "Add")
    {
        visitor = new AddVisitor();
        if(strlist[1] == "staff")
        {
            if(visitor->QueryStaff(query))
            {
                ans = "success";
            }
            else
                ans = "fail";
        }
        else if(strlist[1] == "course")
        {
            if(visitor->QueryCourse(query))
            {
                ans = "success";
            }
            else
                ans = "fail";
        }
        else if(strlist[1] == "activity")
        {
            if(visitor->QueryActivity(query))
            {
                ans = "success";
            }
            else
                ans = "fail";
        }
        else if(strlist[1] == "department")
        {
            if(visitor->QueryDepartment(query))
            {
                ans = "success";
            }
            else
                ans = "fail";
        }
        else
            ans = "fail";
    }
    else if(strlist[0] == "Send" || strlist[0] == "Join")
    {
        visitor = new AddVisitor();
        ans = visitor->QueryLetter(query)?"success":"fail";
    }
    else if(strlist[0] == "Enroll")
    {
        visitor = new AddVisitor();
        ans = visitor->QueryCourse(query)?"success":"fail";
    }
    else if(strlist[0] == "Del" || strlist[0] == "QuitCourse" || strlist[0] == "QuitActivity")
    {
        visitor = new DelVisitor();
        if(strlist[1] == "course" || strlist[0] == "QuitCourse")
        {
            ans = visitor->QueryCourse(query)?"success":"fail";
        }
        else if(strlist[1] == "activity" || strlist[0] == "QuitActivity")
        {
            ans = visitor->QueryActivity(query)?"success":"fail";
        }
        else if(strlist[1] == "staff")
        {
            ans = visitor->QueryStaff(query)?"success":"fail";
        }
        else if(strlist[1] == "sentletter" || strlist[1] == "receivedletter")
        {
            ans = visitor->QueryLetter(query)?"success":"fail";
        }
        else if(strlist[1] =="department")
        {
            ans = visitor->QueryDepartment(query)?"success":"fail";
        }
        else
            ans = "fail";
    }
    else if(strlist[1] == "Update")
    {
        visitor = new UpdateVisitor();
        if(strlist[2] == "staff")
        {
            ans = visitor->QueryStaff(query)?"success":"fail";
        }
        else if(strlist[2] == "activity")
        {
            ans = visitor->QueryActivity(query)?"success":"fail";
        }
        else if(strlist[2] == "letter")
        {
            ans = visitor->QueryLetter(query)?"success":"fail";
        }
        else if(strlist[2] == "department")
        {
            ans = visitor->QueryDepartment(query)?"success":"fail";
        }
        else if(strlist[2] == "course")
        {
            ans = visitor->QueryCourse(query)?"success":"fail";
        }
        else
            ans = "fail";
    }
    else if(strlist[1] == "Get" || strlist[0] == "Get")
    {
        visitor = new GetVisitor();
        if(strlist[2] == "staff")
        {
            ans = visitor->QueryStaff(query)?"success":"fail";
        }
        else if(strlist[2] == "letter")
        {
            ans = visitor->QueryLetter(query)?"success":"fail";
        }
        else if(strlist[2] == "course")
        {
            ans = visitor->QueryCourse(query)?"success":"fail";
        }
        else if(strlist[2] == "activity")
        {
            ans = visitor->QueryActivity(query)?"success":"fail";
        }
        else if(strlist[1] == "department")
        {
            ans = visitor->QueryDepartment(query)?"success":"fail";
        }
    }
    else ans ="wrong form";
    delete visitor;
    return ans;
}

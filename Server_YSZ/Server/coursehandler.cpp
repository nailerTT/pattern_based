#include "coursehandler.h"
#include "QStringList"
CourseHandler::CourseHandler()
    :cs("coursecnn_cs"+QString::number(GetANewId()),"staffcoursecnn_cs"+QString::number(GetANewId()),"staffcnn_cs"+QString::number(GetANewId()))
{

}

bool CourseHandler::Get(const QList<QString> &ids, const QString &property, QString &ref)
{
    unsigned int id = ids[0].toUInt();
    if(property == "all")
    {
        QList<unsigned int> list;
        if(cs.GetCourseList(list))
        {
            for(int i=0;i<list.size();i++)
            {
                QString one = QString::number(list[i]);
                if(i!=list.size()-1)
                    one +=",";
                ref.append(one);
            }
            return true;
        }
        else return false;
    }
    else if(property == "name")
    {
        return cs.GetCourseName(id,ref);
    }
    else if(property == "departmentid")
    {
        unsigned int _id;
        if(cs.GetDepartmentOfACourse(id,_id))
        {
            ref = QString::number(_id);
            return true;
        }
        else return false;

    }
    else if(property == "decription")
    {
        return cs.GetCourseDescription(id,ref);
    }
    else if(property == "isMandatory")
    {
        return cs.GetIsMandatory(id,ref);
    }
    else if(property == "isComposite")
    {
        return cs.GetIsComposite(id,ref);
    }
    else if(property == "compositeCourses")
    {
        QList<unsigned int> list;
        if(cs.GetSubCourses(id,list))
        {
            for(int i=0;i<list.size();i++)
            {
                QString one = QString::number(list[i]);
                if(i!=list.size()-1)
                    one += ",";
                ref +=(one);
            }
            return true;
        }
        else return false;
    }
    else return false;
}

bool CourseHandler::ADD(const QList<QString> &values, QString &ref)
{
    //name,departmentid,description,ismandatory,iscomposite,composite_courses,lecturer
    if(values.size() == 7){
        QString name = values[0];
        QString deptid = values[1];
        QString description = values[2];
        bool ismandatory = values[3].toLower() =="y";
        bool iscomposite = values[4].toLower() == "y";
        unsigned int lecturerid = values[6].toUInt();
        if(iscomposite)
        {
            QStringList subcourses = values[5].split("|");
            QList<unsigned int> ids;
            for(int i=0;i<subcourses.size();i++)
                ids.append(subcourses[i].toUInt());

            return cs.AddACompositeCourse(name,deptid.toUInt(),description,ismandatory,ids,lecturerid,{},{});
        }
        else
        {
            return cs.AddASingleCourse(name,deptid.toUInt(),description,ismandatory,lecturerid,{},{});
        }
    }
    //courseid,staffid
    else if(values.size() == 2)
    {
        unsigned int courseid = values[0].toUInt();
        unsigned int staffid = values[1].toUInt();
        return cs.Enroll(courseid,staffid);
    }
    else return false;
}

bool CourseHandler::Del(const QList<QString> &id)
{
    //{Del,course,courseid}
    //{QuitCourse,courseid,staffid}
    if(id.size() == 0)
        return false;
    if(id.at(0) == "Del")
        return cs.DelCourse(id[2].toUInt());
    else if(id.at(0) == "QuitCourse")
        return cs.Quit(id[1].toUInt(),id[2].toUInt());
}

bool CourseHandler::Update(const QList<QString> &id, const QPair<QString, QString> field_value)
{
    if(id.size() == 0)
        return false;
    unsigned int courseid = id[0].toUInt();
    QString field = field_value.first;
    if(field == "departmentid")
    {
        unsigned int deptid = field_value.second.toUInt();
        return cs.SetDepartmentOfACourse(courseid,deptid);
    }
    else if(field == "name")
    {
        return cs.SetCourseName(courseid,field_value.second);
    }
    else if(field == "description")
    {
        return cs.SetCourseDescription(courseid,field_value.second);
    }
    else if(field == "isMandatory")
    {
        return cs.SetIsMandatory(courseid,field_value.second == "y");
    }
    else if(field == "isComposite")
    {
        return cs.SetIsComposite(courseid,field_value.second=="y");
    }
    else return false;
}

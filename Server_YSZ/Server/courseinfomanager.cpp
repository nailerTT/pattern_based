#include "courseinfomanager.h"

CourseInfoManager::CourseInfoManager(QString cn)
    :InfoManager(cn)
{

}

CourseInfoManager::~CourseInfoManager()
{

}

bool CourseInfoManager::AddSingleCourse(QString name, unsigned int dept_id, QString description, bool mandatory)
{
    QString _dept_id = QString::number(dept_id);
    QString is_mandatory = mandatory?"y":"n";
    QString _des = "'"+description+"'";
    QString isman = "'" + is_mandatory + "'";
    QString _name = "'" + name + "'";
    return ddba.Add("course",{"courseName","Department_DepartmentID","Description","IsMandatory","IsComposite"},{_name,_dept_id,_des,isman,"'n'"});
}
bool CourseInfoManager::AddCompositeCourse(QString name, unsigned int dept_id, QString descrption, bool mandatory, QList<unsigned int> sub_courses)
{
    QString _dept_id = QString::number(dept_id);
    QString is_mandatory = mandatory?"'y'":"'n'";
    QString sub_courseids = "'{";
    bool check = true;
    for(int i=0;i<sub_courseids.size();i++)
    {
        unsigned int id = sub_courses[i];
        if(ddba.Ask("course",{"courseid="+QString::number(id)},{"*"}))
        {
            check = ddba.HasNext();
            if(!check)
                break;
        }else{
            check = false;
            break;
        }
    }
    if(!check)
    {
        return false;
    }
    for(int i=0;i<sub_courses.size();i++)
    {
        sub_courseids += QString::number(sub_courses[i]);
        if(i!=sub_courses.size()-1)
        {
            sub_courseids += ",";
        }
    }
    sub_courseids += "}'";
    QString _name = "'"+name+"'";
    QString des = "'"+descrption+"'";
    return ddba.Add("course",{"courseName","Department_DepartmentID","Description","IsMandatory","IsComposite","composite_courses"},{_name,_dept_id,des,is_mandatory,"'y'",sub_courseids});
}

bool CourseInfoManager::DelCourse(unsigned int id)
{
    QString instr = "instr(composite_courses,',"+QString::number(id) + ",')>0 or " + "instr(composite_courses,'{"+QString::number(id)+",')>0";
    if(ddba.Ask("course",{"iscomposite = 'y'",instr},{"courseid"}))
    {
        QList<unsigned int> affected_courses;
        affected_courses.append(id);
        while(ddba.HasNext())
        {
            unsigned int _id = ddba.FetchNextRow()[0].toUInt();
            affected_courses.append(_id);
        }
        for(int i=0;i<affected_courses.size();i++)
        {
            ddba.Del("course",{"courseid="+QString::number(affected_courses[i])});
        }
        return true;
    }
    else{
        return false;
    }
}

bool CourseInfoManager::GetCourseName(unsigned int id, QString &ans)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"coursename"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such course wherer course id="+QString::number(id);
            return false;
        }
        QString name = ddba.FetchNextRow()[0];
        ans = name;
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool CourseInfoManager::SetCourseName(unsigned int id, const QString &name)
{
    return ddba.Mod("course",{"courseid="+QString::number(id)},{"CourseName"},{name});
}

bool CourseInfoManager::GetCourseNames(const QList<unsigned int> courseids, QList<QString> &names)
{
    bool check = false;
    for(int i=0;i<courseids.size();i++)
    {
        QString name = "";
        check = GetCourseName(courseids[i],name);
        names.append(name);
    }
    return check;
}

bool CourseInfoManager::GetCourseDescription(unsigned int id, QString &ans)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"description"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such course wherer course id="+QString::number(id);
            return false;
        }
        QString des = ddba.FetchNextRow()[0];
        ans = des;
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool CourseInfoManager::SetCourseDescription(unsigned int id, const QString &description)
{
    return ddba.Mod("course",{"courseid="+QString::number(id)},{"description"},{description});
}

bool CourseInfoManager::GetDepartment(const unsigned int id, unsigned int &dept)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"Department_DepartmentID"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        dept = ddba.FetchNextRow()[0].toUInt();
    }
    else{
        return false;
    }
}

bool CourseInfoManager::GetDepartmentName(unsigned int id, QString &ans)
{
    unsigned int deptid;
    if(GetDepartment(id,deptid))
    {
        ans = "";
        GetDepartmentName(deptid,ans);
        return true;
    }
    else return false;
}

bool CourseInfoManager::GetIsMandatory(unsigned int id, QString &ans)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"isMandatory"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such course wherer course id="+QString::number(id);
            return false;
        }
        QString res = ddba.FetchNextRow()[0];
        ans = res;
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool CourseInfoManager::SetIsMandatory(unsigned int id, bool val)
{
    return ddba.Mod("course",{"courseid="+QString::number(id)},{"IsMandatory"},{val?"'y'":"'n'"});
}

bool CourseInfoManager::GetIsComposite(unsigned int id, QString &ans)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"IsComposite"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such course wherer course id="+QString::number(id);
            return false;
        }
        QString res = ddba.FetchNextRow()[0];
        ans = res;
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool CourseInfoManager::SetIsComposite(unsigned int id, bool val)
{
    return ddba.Mod("course",{"courseid="+QString::number(id)},{"IsComposite"},{val?"'y'":"'n'"});
}

bool CourseInfoManager::GetSubCourses(unsigned int id, QList<unsigned int> &sub_ids)
{
    if(ddba.Ask("course",{"courseid="+QString::number(id)},{"composite_courses"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        QString row = ddba.FetchNextRow()[0];
        QList<QString> idstrs = row.mid(1,row.length()-2).split(",");
        for(int i=0;i<idstrs.size();i++)
        {
            sub_ids.append(idstrs[i].toUInt());
        }
        return true;
    }
    else{
        return false;
    }
}

bool CourseInfoManager::GetCourseList(QList<unsigned int>& list)
{
    if(ddba.Ask("course",{},{"courseid"}))
    {
        while(ddba.HasNext())
        {
            list.append(ddba.FetchNextRow()[0].toUInt());
        }
        return true;
    }
    else
        return false;
}

bool CourseInfoManager::SetDepartment(unsigned int courseid, unsigned int deptid)
{
    return ddba.Mod("course",{"courseid="+QString::number(courseid)},{"Department_DepartmentID"},{QString::number(deptid)});
}

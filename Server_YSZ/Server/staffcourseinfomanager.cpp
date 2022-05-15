#include "staffcourseinfomanager.h"

StaffCourseInfoManager::StaffCourseInfoManager(QString cn)
    :InfoManager(cn)
{

}

StaffCourseInfoManager::~StaffCourseInfoManager()
{
}
QString get_role_str(Role role)
{
    QString _role;
    switch(role)
    {
    case Role::Student:default:
        _role = "'Student'";break;
    case Role::Deputy:
        _role = "'Deputy'";break;
    case Role::Main:
        _role = "'Main'";break;
    case Role::TA:
        _role = "'TA'";break;
    }
    return _role;
}
Role get_role_from_str(const QString& str)
{
    Role role = Role::Student;
    if(str == "Main")
        role = Role::Main;
    else if(str == "Deputy")
        role = Role::Deputy;
    else if(str == "TA")
        role = Role::TA;
    return role;
}

bool StaffCourseInfoManager::AddARelation(const unsigned int staffid, const unsigned int courseid, Role role)
{
    return ddba.Add("staff_has_course",{"Staff_StaffID","Course_CourseID","Role"},{QString::number(staffid),QString::number(courseid),get_role_str(role)});
}

bool StaffCourseInfoManager::DelARelation(const unsigned int staffid, const unsigned int courseid)
{
    return ddba.Del("staff_has_course",{"Staff_StaffID="+QString::number(staffid),"Course_CourseID="+QString::number(courseid)});
}

bool StaffCourseInfoManager::DelACourse(const unsigned int courseid)
{
    return ddba.Del("staff_has_course",{"Course_CourseID="+QString::number(courseid)});
}

bool StaffCourseInfoManager::DelAStaff(const unsigned int staffid)
{
    return ddba.Del("staff_has_course",{"Staff_StaffID="+QString::number(staffid)});
}

bool StaffCourseInfoManager::SetRole(const unsigned int staffid, const unsigned int courseid, Role role)
{
    return ddba.Mod("staff_has_course",{"Staff_StaffID="+QString::number(staffid),"Course_CourseID="+QString::number(courseid)},{"role"},{get_role_str(role)});
}

bool StaffCourseInfoManager::GetRole(const unsigned int staffid, const unsigned int courseid, Role &role)
{
    if(ddba.Ask("staff_has_course",{"Staff_StaffID="+QString::number(staffid),"Course_CourseID="+QString::number(courseid)},{"role"}))
    {
        if(ddba.HasNext()==0)
        {
            return false;
        }
        role = get_role_from_str(ddba.FetchNextRow()[0]);
        return true;
    }
    else{
        return false;
    }
}

bool StaffCourseInfoManager::RemoveTas(const unsigned int courseid)
{
    return ddba.Del("staff_has_course",{"Course_CourseID="+QString::number(courseid),"Role='TA'"});
}

bool StaffCourseInfoManager::GetCoursesIdsOfAMainLecturer(const unsigned int staffid, QList<unsigned int> &ids)
{
    return GetCourseIdsOfStaff(staffid,Role::Main,ids);
}

bool StaffCourseInfoManager::GetCoursesIdsOfAStudent(const unsigned int staffid, QList<unsigned int> &ids)
{
    return GetCourseIdsOfStaff(staffid,Role::Student,ids);
}

bool StaffCourseInfoManager::GetCoursesIdsOfATA(const unsigned int staffid, QList<unsigned int> &ids)
{
    return GetCourseIdsOfStaff(staffid,Role::TA,ids);
}

bool StaffCourseInfoManager::GetCoursesIdsOfADeputy(const unsigned int staffid, QList<unsigned int> &ids)
{
    return GetCourseIdsOfStaff(staffid,Role::Deputy,ids);
}


bool StaffCourseInfoManager::GetMain(const unsigned int courseid, unsigned int &main)
{
    if(ddba.Ask("staff_has_course",{"Course_CourseID="+QString::number(courseid)},{"Role"}))
    {
        if(ddba.HasNext())
        {
            if(ddba.HasNext()==false)
            {
                return false;
            }
            main = ddba.FetchNextRow()[0].toUInt();
            return true;
        }
    }
    else{
        return false;
    }
}
bool StaffCourseInfoManager::GetStaffs(const unsigned int courseid,Role role,QList<unsigned int>& staffids)
{
    QString _role = get_role_str(role);
    if(ddba.Ask("staff_has_course",{"Course_CourseID="+QString::number(courseid),"Role="+_role},{"Staff_StaffID"}))
    {

        while(ddba.HasNext())
        {
            staffids.append(ddba.FetchNextRow()[0].toUInt());
        }
        return true;;
    }
    else{
        return false;
    }
}

bool StaffCourseInfoManager::GetTAs(const unsigned int courseid, QList<unsigned int> &Tas)
{
    return GetStaffs(courseid,Role::TA,Tas);
}

bool StaffCourseInfoManager::GetDeputies(const unsigned int courseid, QList<unsigned int> &deputies)
{
    return GetStaffs(courseid,Role::Deputy,deputies);
}

bool StaffCourseInfoManager::GetStudents(const unsigned int courseid, QList<unsigned int> &students)
{
    return GetStaffs(courseid,Role::Student,students);
}

bool StaffCourseInfoManager::GetCourseIdsOfStaff(const unsigned int staffid, Role role, QList<unsigned int> &ids)
{
    QString _role = "'" + get_role_str(role) + "'";
    if(ddba.Ask("staff_has_course",{"Staff_StaffID="+QString::number(staffid)},{"Course_CourseID"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        else{
            while(ddba.HasNext())
            {
                ids.append(ddba.FetchNextRow()[0].toUInt());
            }
            return true;
        }
    }
    else{
        return false;
    }
}

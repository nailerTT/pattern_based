#include "coursesystem.h"
#include "QPair"
CourseSystem::CourseSystem(const QString& course_cnn, const QString& staffcourse_cnn, const QString &staff_cnn )
    : InfoManager(""),cim(course_cnn),scim(staffcourse_cnn),sim(staff_cnn)
{

}

bool CourseSystem::AddASingleCourse(QString name, unsigned int dept_id, QString description, bool mandatory, const unsigned int lecturerid, const QList<unsigned int> &deputies, const QList<unsigned int> &TAs)
{
    if(cim.AddSingleCourse(name,dept_id,description,mandatory))
    {
        unsigned int courseid = cim.GetLastInsertID();
        scim.AddARelation(lecturerid,courseid,Role::Main);
        for(int i=0;i<deputies.size();i++)
        {
            scim.AddARelation(deputies[i],courseid,Role::Deputy);
        }
        for(int i=0;i<TAs.size();i++)
        {
            scim.AddARelation(TAs[i],courseid,Role::TA);
        }
        return true;
    }
    else{
        return false;
    }

}

bool CourseSystem::AddACompositeCourse(QString name, unsigned int dept_id, QString descrption, bool mandatory, const QList<unsigned int>& sub_courses, const unsigned int lecturerid, const QList<unsigned int> &deputies, const QList<unsigned int> &TAs)
{
    if(cim.AddCompositeCourse(name,dept_id,descrption,mandatory,sub_courses))
    {
        unsigned int courseid = cim.GetLastInsertID();
        scim.AddARelation(lecturerid,courseid,Role::Main);
        for(int i=0;i<deputies.size();i++)
        {
            scim.AddARelation(deputies[i],courseid,Role::Deputy);
        }
        for(int i=0;i<TAs.size();i++)
        {
            scim.AddARelation(TAs[i],courseid,Role::TA);
        }
        return true;
    }
    else{
        return false;
    }
}

bool CourseSystem::DelAStaff(unsigned int id)
{
    return scim.DelAStaff(id);
}

bool CourseSystem::DelCourse(unsigned int id)
{
    return scim.DelACourse(id) && cim.DelCourse(id);
}

bool CourseSystem::GetCourseName(unsigned int id, QString &ans)
{
    return cim.GetCourseName(id,ans);
}

bool CourseSystem::SetCourseName(unsigned int id,const  QString &name)
{
    return cim.SetCourseName(id,name);
}

bool CourseSystem::GetCourseDescription(unsigned int id, QString &ans)
{
    return cim.GetCourseDescription(id,ans);
}

bool CourseSystem::GetCourseList(QList<unsigned int> &lists)
{
    return cim.GetCourseList(lists);
}

bool CourseSystem::GetCourseMain(const unsigned int courseid, unsigned int &mainid)
{
    return scim.GetMain(courseid,mainid);
}

bool CourseSystem::GetCourseMain(const unsigned int courseid, QString &main_name)
{
    unsigned int id;
    if(scim.GetMain(courseid,id))
    {
        if(sim.GetName(id,main_name)==false)
            main_name = "";
        return true;
    }
    else
        return false;
}

bool CourseSystem::GetCourseStudents(const unsigned int courseid, QList<unsigned int> &students)
{
    return scim.GetStudents(courseid,students);
}

bool CourseSystem::GetCourseStudents(const unsigned int courseid, QList<QString> &students)
{
    QList<unsigned int> stuids;
    if(scim.GetStudents(courseid,stuids))
    {
        sim.getNames(stuids,students);
        return true;
    }
    else
        return false;
}

bool CourseSystem::GetCourseDeputies(const unsigned int courseid, QList<unsigned int> &deputies)
{
    return scim.GetDeputies(courseid,deputies);
}

bool CourseSystem::GetCourseDeputies(const unsigned int courseid, QList<QString> &deputies)
{
    QList<unsigned int> deputyids;
    if(scim.GetDeputies(courseid,deputyids))
    {
        sim.getNames(deputyids,deputies);
        return true;
    }
    else
        return false;
}

bool CourseSystem::GetCourseTAs(const unsigned int courseid, QList<unsigned int> &TAs)
{
    return scim.GetTAs(courseid,TAs);
}

bool CourseSystem::GetCourseTAs(const unsigned int courseid, QList<QString> &TAs)
{
    QList<unsigned int> deputyids;
    if(scim.GetDeputies(courseid,deputyids))
    {
        sim.getNames(deputyids,TAs);
        return true;
    }
    else
        return false;
}

bool CourseSystem::GetTaughtCourses(const unsigned int staffid,QList<unsigned int> &lists)
{
    return scim.GetCoursesIdsOfAMainLecturer(staffid,lists);
}

bool CourseSystem::GetTaughtCourses(const unsigned int staffid, QList<QString> &lists)
{
    QList<unsigned int> courseids;
    if(GetTaughtCourses(staffid,courseids))
    {
        cim.GetCourseNames(courseids,lists);
        return true;
    }
    else return false;
}

bool CourseSystem::GetEnrolledCourses(const unsigned int staffid,QList<unsigned int> &list)
{
    return scim.GetCoursesIdsOfAStudent(staffid,list);
}

bool CourseSystem::GetEnrolledCourses(const unsigned int staffid, QList<QString> &list)
{
    QList<unsigned int> courseids;
    if(GetEnrolledCourses(staffid,courseids))
    {
        cim.GetCourseNames(courseids,list);
        return true;
    }
    else return false;
}

bool CourseSystem::GetCoursesAsTA(const unsigned int staffid, QList<unsigned int> &list)
{
    return scim.GetCoursesIdsOfATA(staffid,list);
}

bool CourseSystem::GetCoursesAsTA(const unsigned int staffid, QList<QString> &list)
{
    QList<unsigned int> courseids;
    if(GetCoursesAsTA(staffid,courseids))
    {
        cim.GetCourseNames(courseids,list);
        return true;
    }
    else return false;
}

bool CourseSystem::GetCoursesAsDeputy(const unsigned int staffid, QList<unsigned int> &list)
{
    return scim.GetCoursesIdsOfAStudent(staffid,list);
}

bool CourseSystem::GetCoursesAsDeputy(const unsigned int staffid, QList<QString> &list)
{
    QList<unsigned int> courseids;
    if(GetCoursesAsDeputy(staffid,courseids))
    {
        cim.GetCourseNames(courseids,list);
        return true;
    }
    else return false;
}

bool CourseSystem::AddTas(const unsigned int courseid, QList<unsigned int> &staffids)
{
    bool check = false;
    for(int i=0;i<staffids.size();i++)
    {
        check = scim.AddARelation(staffids[i],courseid,Role::TA);
    }
    return check;
}

bool CourseSystem::ResetTas(const unsigned int courseid, QList<unsigned int> &new_TAs)
{
    if(scim.RemoveTas(courseid))
    {
        return AddTas(courseid,new_TAs);
    }
    else{
        return false;
    }
}

bool CourseSystem::Enroll(const unsigned int courseid, const unsigned int stuid)
{
    return scim.AddARelation(stuid,courseid,Role::Student);
}

bool CourseSystem::Quit(const unsigned int courseid, const unsigned int stuid)
{
    return scim.DelARelation(stuid,courseid);
}

bool CourseSystem::SetCourseDescription(unsigned int id, const QString &description)
{
    return cim.SetCourseDescription(id,description);
}

bool CourseSystem::GetDepartmentName(unsigned int id, QString &ans)
{
    return cim.GetDepartmentName(id,ans);
}

bool CourseSystem::GetIsMandatory(unsigned int id, QString &ans)
{
    return cim.GetIsMandatory(id,ans);
}

bool CourseSystem::SetIsMandatory(unsigned int id, bool val)
{
    return cim.SetIsMandatory(id,val);
}

bool CourseSystem::GetIsComposite(unsigned int id, QString &ans)
{
    return cim.GetIsComposite(id,ans);
}

bool CourseSystem::SetIsComposite(unsigned int id, bool val)
{
    return cim.SetIsComposite(id,val);
}

bool CourseSystem::GetSubCourses(unsigned int id, QList<unsigned int> &sub_ids)
{
    return cim.GetSubCourses(id,sub_ids);
}

bool CourseSystem::GetSubCourses(unsigned int id, QList<QString> &names)
{
    QList<unsigned int> subcourse_ids;
    if(GetSubCourses(id,subcourse_ids))
    {
        return cim.GetCourseNames(subcourse_ids,names);
    }
    else return false;
}

bool CourseSystem::GetRoleInACourse(const unsigned int courseid, const unsigned int staffid,Role& role)
{
    return scim.GetRole(staffid,courseid,role);
}

bool CourseSystem::GetDepartmentOfACourse(const unsigned int courseid,unsigned int& deptid)
{
    return cim.GetDepartment(courseid,deptid);
}

bool CourseSystem::SetDepartmentOfACourse(const unsigned int courseid, const unsigned int &deptid)
{
    return cim.SetDepartment(courseid,deptid);
}



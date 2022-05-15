#ifndef STAFFCOURSEINFOMANAGER_H
#define STAFFCOURSEINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
enum class Role{
    Student,Deputy,Main,TA
};

class StaffCourseInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit StaffCourseInfoManager(QString cn);
    ~StaffCourseInfoManager();
    bool AddARelation(const unsigned int staffid,const unsigned int courseid,Role role);
    bool DelARelation(const unsigned int staffid,const unsigned int courseid);
    bool DelACourse(const unsigned int courseid);
    bool DelAStaff(const unsigned int staffid);
    bool SetRole(const unsigned int staffid,const unsigned int courseid, Role role);
    bool GetRole(const unsigned int staffid,const unsigned int courseid, Role& role);
    bool RemoveTas(const unsigned int courseid);
    bool GetCoursesIdsOfAMainLecturer(const unsigned int staffid,QList<unsigned int>& ids);
    bool GetCoursesIdsOfAStudent(const unsigned int staffid,QList<unsigned int>& ids);
    bool GetCoursesIdsOfATA(const unsigned int staffid,QList<unsigned int>& ids);
    bool GetCoursesIdsOfADeputy(const unsigned int staffid,QList<unsigned int>& ids);
    bool GetMain(const unsigned int courseid,unsigned int& main);
    bool GetTAs(const unsigned int courseid,QList<unsigned int>& Tas);
    bool GetDeputies(const unsigned int courseid,QList<unsigned int>& deputies);
    bool GetStudents(const unsigned int courseid,QList<unsigned int>& students);
signals:
private:
    bool GetCourseIdsOfStaff(const unsigned int staffid,Role role,QList<unsigned int>& ids);
    bool GetStaffs(const unsigned int courseid,Role role,QList<unsigned int>& staffids);
};

#endif // STAFFCOURSEINFOMANAGER_H

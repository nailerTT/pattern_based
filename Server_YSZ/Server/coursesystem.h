#ifndef COURSESYSTEM_H
#define COURSESYSTEM_H

#include <QObject>
#include "courseinfomanager.h"
#include "staffcourseinfomanager.h"
#include "staffinfomanager.h"
class CourseSystem : public InfoManager
{
    Q_OBJECT
public:
    explicit CourseSystem(const QString& course_cnn="coursecnn_cs",const QString& staffcourse_cnn = "staffcoursecnn_cs",const QString& staff_cnn = "staffcnn_cs");
    bool AddASingleCourse(QString name, unsigned int dept_id,QString description, bool mandatory,const unsigned int lecturerid,const QList<unsigned int>& deputies, const QList<unsigned int>& TAs );
    bool AddACompositeCourse(QString name, unsigned int dept_id, QString descrption, bool mandatory, const QList<unsigned int> &sub_courses, const unsigned int lecturerid, const QList<unsigned int>& deputies, const QList<unsigned int>& TAs);
    bool DelAStaff(unsigned int id);
    bool DelCourse(unsigned int id);
    bool GetCourseName(unsigned int id,QString& ans);
    bool SetCourseName(unsigned int id, const QString &name);
    bool GetCourseDescription(unsigned int id,QString& ans);
    bool GetCourseList(QList<unsigned int>& lists);
    bool GetCourseMain(const unsigned int courseid,unsigned int& mainid);
    bool GetCourseMain(const unsigned int courseid,QString& main_name);
    bool GetCourseStudents(const unsigned int courseid,QList<unsigned int>& students);
    bool GetCourseStudents(const unsigned int courseid,QList<QString>& students);
    bool GetCourseDeputies(const unsigned int courseid,QList<unsigned int>& deputies);
    bool GetCourseDeputies(const unsigned int courseid,QList<QString>& deputies);
    bool GetCourseTAs(const unsigned int courseid,QList<unsigned int>& TAs);
    bool GetCourseTAs(const unsigned int courseid,QList<QString>& TAs);
    bool GetTaughtCourses(const unsigned int staffid, QList<unsigned int>& lists);
    bool GetTaughtCourses(const unsigned int staffid,QList<QString>& lists);
    bool GetEnrolledCourses(const unsigned int staffid, QList<unsigned int>& list);
    bool GetEnrolledCourses(const unsigned int staffid, QList<QString> &list);
    bool GetCoursesAsTA(const unsigned int staffid,QList<unsigned int>& list);
    bool GetCoursesAsTA(const unsigned int staffid,QList<QString>& list);
    bool GetCoursesAsDeputy(const unsigned int staffid,QList<unsigned int>& list);
    bool GetCoursesAsDeputy(const unsigned int staffid,QList<QString>& list);
    bool AddTas(const unsigned int courseid,QList<unsigned int>& staffids);
    bool ResetTas(const unsigned int courseid,QList<unsigned int>& new_TAs);
    bool Enroll(const unsigned int courseid,const unsigned int stuid);
    bool Quit(const unsigned int courseid,const unsigned int stuid);
    bool SetCourseDescription(unsigned int id, const QString& description);
    bool GetDepartmentName(unsigned int id, QString& ans);
    bool GetIsMandatory(unsigned int id, QString& ans);
    bool SetIsMandatory(unsigned int id, bool val);
    bool GetIsComposite(unsigned int id, QString& ans);
    bool SetIsComposite(unsigned int id, bool val);
    bool GetSubCourses(unsigned int id, QList<unsigned int>& sub_ids);
    bool GetSubCourses(unsigned int id, QList<QString>& names);
    bool GetRoleInACourse(const unsigned int courseid, const unsigned int staffid, Role &role);
    bool GetDepartmentOfACourse(const unsigned int courseid, unsigned int &deptid);
    bool SetDepartmentOfACourse(const unsigned int courseid, const unsigned int &deptid);
signals:
private:
    CourseInfoManager cim;
    StaffCourseInfoManager scim;
    StaffInfoManager sim;
};

#endif // COURSESYSTEM_H

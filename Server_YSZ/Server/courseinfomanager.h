#ifndef COURSEINFOMANAGER_H
#define COURSEINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
class CourseInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit CourseInfoManager(QString cn);
    ~CourseInfoManager();
    bool AddSingleCourse(QString name, unsigned int dept_id,QString description, bool mandatory);
    bool AddCompositeCourse(QString name, unsigned int dept_id,QString descrption,bool mandatory,QList<unsigned int> sub_courses);
    bool DelCourse(unsigned int id);
    bool GetCourseName(unsigned int id,QString& ans);
    bool SetCourseName(unsigned int id,const QString& name);
    bool GetCourseNames(const QList<unsigned int> courseids,QList<QString>& names);
    bool GetCourseDescription(unsigned int id,QString& ans);
    bool SetCourseDescription(unsigned int id, const QString& description);
    bool GetDepartment(const unsigned int id,unsigned int& dept);
    bool GetDepartmentName(unsigned int id, QString& ans);
    bool GetIsMandatory(unsigned int id, QString& ans);
    bool SetIsMandatory(unsigned int id, bool val);
    bool GetIsComposite(unsigned int id, QString& ans);
    bool SetIsComposite(unsigned int id, bool val);
    bool GetSubCourses(unsigned int id, QList<unsigned int>& sub_ids);
    bool GetCourseList(QList<unsigned int> &list);
    bool SetDepartment(unsigned int courseid,unsigned int deptid);
signals:
};

#endif // COURSEINFOMANAGER_H

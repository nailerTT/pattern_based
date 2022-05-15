#ifndef STAFFINFOMANAGER_H
#define STAFFINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
enum class RegisterState{
    Full,Pending,Not
};
class StaffInfoManager : public InfoManager
{
    Q_OBJECT
public:
    using ID = unsigned int;
    explicit StaffInfoManager(QString cn);
    ~StaffInfoManager();
    bool GetName(ID id,QString& ans);
    bool getNames(const QList<ID> &id, QList<QString>& names);
    bool SetName(unsigned int id,const QString& name);
    bool GetDepartmentName(ID id, QString &ans);
    bool GetDepartment(ID id,QString& ans);
    bool GetRegisterStatus(ID id, QString &ans);
    bool SetStaffState(ID id,RegisterState state);
    bool AddNewStudent(QString name,ID department_id,bool gender, RegisterState rt = RegisterState::Not,const QString& password = "123456");
    bool AddNewStaff(QString name,ID department_id,bool gender,const QString& password = "123456");
    bool DelStaff(ID id);
    bool SetDepartment(ID staff_id,ID dept_id);
    bool IsStudent(ID id, QString &ans);
    bool GetGender(ID id,QString& ans);
    bool GetPassword(ID id, QString& password);
    bool SetPassword(ID id, const QString& password);
    bool GetRole(ID id, QString& role);
signals:
private:
};

#endif // STAFFINFOMANAGER_H

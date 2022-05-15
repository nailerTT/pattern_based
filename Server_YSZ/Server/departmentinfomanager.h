#ifndef DEPARTMENTINFOMANAGER_H
#define DEPARTMENTINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
class DepartmentInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit DepartmentInfoManager(QString cn);
    ~DepartmentInfoManager(){}
    bool AddDepartment(QString department_name);
    bool DelDepartment(unsigned int id);
    bool GetDepartmentName(unsigned int id,QString& name);
    bool GetDepartmentId(const QString&name,unsigned int& id);
    bool SetDepartmentName(unsigned int id,QString new_name);
signals:
};

#endif // DEPARTMENTINFOMANAGER_H

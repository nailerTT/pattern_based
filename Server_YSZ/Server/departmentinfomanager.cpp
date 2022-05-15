#include "departmentinfomanager.h"

DepartmentInfoManager::DepartmentInfoManager(QString cn)
    :InfoManager(cn)
{

}

bool DepartmentInfoManager::AddDepartment(QString department_name)
{
    QString _name = "'"+department_name+"'";
    return ddba.Add("department",{"departmentname"},{_name});
}

bool DepartmentInfoManager::DelDepartment(unsigned int id)
{
    return ddba.Del("department",{"departmentid="+QString::number(id)});
}

bool DepartmentInfoManager::GetDepartmentName(unsigned int id, QString &name)
{
    if(ddba.Ask("department",{"departmentid="+QString::number(id)},{"departmentname"}))
    {
        if(ddba.HasNext()==false)
        {
            name = "no such department which's id =" + QString::number(id);
            return false;
        }
        else{
            QString s = ddba.FetchNextRow()[0];
            name = s;
            return true;
        }
    }
    else{
        name = ddba.FetchErrorMSG();
        return false;
    }
}

bool DepartmentInfoManager::GetDepartmentId(const QString &name, unsigned int &id)
{
    QString _name = "'"+name+"'";
    if(ddba.Ask("department",{"DepartmentName="+_name},{"departmentid"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        else{
            QString s = ddba.FetchNextRow()[0];
            id = s.toUInt();
            return true;
        }
    }
    else{
        return false;
    }
}

bool DepartmentInfoManager::SetDepartmentName(unsigned int id, QString new_name)
{
    QString _name = "'" + new_name +"'";
    return ddba.Mod("department",{"departmentid="+QString::number(id)},{"departmentname"},{_name});
}

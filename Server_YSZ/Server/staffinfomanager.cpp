#include "staffinfomanager.h"

StaffInfoManager::StaffInfoManager(QString cn)
    :InfoManager(cn)
{

}

StaffInfoManager::~StaffInfoManager()
{
    ddba.Disconnect();
}

bool StaffInfoManager::GetName(ID id, QString &ans)
{
    QString _id = QString::number(id);
    if(ddba.Ask("staff",{QString("staffid="+ _id)},{"staffname"}))
    {
        auto rows = ddba.FetchNextRow();
        if(rows.size() == 0)
        {
            ans = "no such staff";
            return false;
        }
        ans = rows.at(0);
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool StaffInfoManager::getNames(const QList<ID>& id, QList<QString> &names)
{
    bool check = true;
    for(int i=0;i<id.size();i++)
    {
        QString name;
        check = GetName(id[i],name);
        names.append(name);
    }
    return check;
}

bool StaffInfoManager::SetName(unsigned int id, const QString &name)
{
    return ddba.Mod("staff",{"staffid="+QString::number(id)},{"staffname"},{name});
}

bool StaffInfoManager::GetDepartmentName(ID id,QString& ans)
{
    if(ddba.Ask("staff",{QString("staffid="+QString::number(id))},{"departmentid"}))
    {
        auto rows = ddba.FetchNextRow();
        if(rows.size() == 0)
        {
            ans = "no such staff: id=" + QString::number(id);
            return false;
        }
        QString dept_id = rows.at(0);
        if(ddba.Ask("department",{"departmentid ="+dept_id},{"departmentname"}))
        {
            rows = ddba.FetchNextRow();
            if(rows.size() == 0)
            {
                ans = "no such staff: id=" + dept_id;
                return false;
            }
            ans = rows.at(0);
            return true;
        }
        else{
            ans = ddba.FetchErrorMSG();
            return false;
        }
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool StaffInfoManager::GetDepartment(ID id, QString &ans)
{
    if(ddba.Ask("staff",{QString("staffid="+QString::number(id))},{"departmentid"}))
    {
        if(ddba.HasNext())
            ans = ddba.FetchNextRow()[0];
        else ans = "";
        return true;
    }
    else return false;
}

bool StaffInfoManager::GetRegisterStatus(ID id,QString& ans)
{
    if(ddba.Ask("staff",{QString("staffid="+QString::number(id))},{"registerstatus"})){
        auto rows = ddba.FetchNextRow();
        if(rows.size() == 0)
        {
            ans = "no such staff: id=" + QString::number(id);
            return false;
        }
        ans = rows.at(0);
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool StaffInfoManager::SetStaffState(ID id, RegisterState state)
{
    QString _state;
    if(state == RegisterState::Full)
        _state = "'Full'";
    else if(state == RegisterState::Not)
        _state = "'NotRegister'";
    else
        _state = "'Pending'";
    return ddba.Mod("staff",{"staffid="+QString::number(id)},{"RegisterStatus"},{_state});
}

bool StaffInfoManager::AddNewStudent(QString name, ID department_id, bool gender, RegisterState rt, const QString &password)
{
    QString _name = "'" + name + "'";
    QString _state;
    if(rt == RegisterState::Full)
        _state = "'Full'";
    else if(rt == RegisterState::Not)
        _state = "'NotRegister'";
    else
        _state = "'Pending'";
    QString _dept_id = QString::number(department_id);
    QString _gender = gender?"'male'":"'female'";
    QString _password = "'" + password+ "'";
    return ddba.Add("staff",{"staffname","registerstatus","departmentid","role","gender","password"},{_name,_state,_dept_id,"'student'",_gender,_password});
}

bool StaffInfoManager::AddNewStaff(QString name, ID department_id, bool gender, const QString &password)
{
    QString _name = "'" + name + "'";
    QString _state = "'NotStudent'";
    QString _dept_id = QString::number(department_id);
    QString _gender = gender?"'male'":"'female'";
    QString _password = "'" + password + "'";
    return ddba.Add("staff",{"staffname","registerstatus","departmentid","role","gender","password"},{_name,_state,_dept_id,"'nonstudent'",_gender,_password});
}

bool StaffInfoManager::DelStaff(ID id)
{
    return ddba.Del("staff",{"staffid="+QString::number(id)});
}

bool StaffInfoManager::SetDepartment(ID staff_id, ID dept_id)
{
    return ddba.Mod("staff",{"staffid="+QString::number(staff_id)},{"departmentid"},{QString::number(dept_id)});
}

bool StaffInfoManager::IsStudent(ID id,QString& ans)
{
    if(ddba.Ask("staff",{"staffid="+QString::number(id)},{"role"}))
    {
        auto rows = ddba.FetchNextRow();
        if(rows.size() == 0)
        {
            ans = "no such staff: id=" + QString::number(id);
            return false;
        }
        QString role = rows.at(0);
        ans = role == "student"?"YES":"NO";
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool StaffInfoManager::GetGender(ID id, QString &ans)
{
    if(ddba.Ask("staff",{"staffid="+QString::number(id)},{"gender"}))
    {
        auto rows = ddba.FetchNextRow();
        if(rows.size() == 0)
        {
            ans = "no such staff: id=" + QString::number(id);
            return false;
        }
        ans = rows.at(0);
        return true;
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool StaffInfoManager::GetPassword(ID id, QString &password)
{
    if(ddba.Ask("staff",{"staffid="+QString::number(id)},{"password"}))
    {
        if(ddba.HasNext())
        {
            password = ddba.FetchNextRow()[0];
        }
        else{
            password = "";
        }
        return true;
    }
    else{
        return false;
    }
}

bool StaffInfoManager::SetPassword(ID id, const QString &password)
{
    QString _password = "'" + password +"'";
    return ddba.Mod("staff",{"staffid="+QString::number(id)},{"password"},{_password});
}

bool StaffInfoManager::GetRole(ID id, QString &role)
{
    if(ddba.Ask("staff",{"staffid="+QString::number(id)},{"role"}))
    {
        if(ddba.HasNext())
        {
            role = ddba.FetchNextRow()[0];
            return true;
        }
        else
            return false;
    }
    else
        return false;
}



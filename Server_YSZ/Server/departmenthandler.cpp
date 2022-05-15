#include "departmenthandler.h"

DepartmentHandler::DepartmentHandler()
    :dim("dhcnn"+QString::number(GetANewId()))
{

}

bool DepartmentHandler::Get(const QList<QString> &ids, const QString &property, QString &ref)
{
    if(property == "departmentid")
    {
        QString name = ids[0];
        unsigned int id;
        if(dim.GetDepartmentId(name,id))
        {
            ref = QString::number(id);
            return true;
        }
        else return false;
    }
    else if(property == "departmentname")
    {
        unsigned int id = ids[0].toUInt();
        if(dim.GetDepartmentName(id,ref))
        {
            return true;
        }
        else return false;
    }
    else return false;
}

bool DepartmentHandler::ADD(const QList<QString> &values, QString &ref)
{
    if(values.size() == 0)
        return false;
    return dim.AddDepartment(values[0]);
}

bool DepartmentHandler::Del(const QList<QString> &id)
{
    if(id.size() == 0)
        return false;
    return dim.DelDepartment(id[0].toUInt());
}

bool DepartmentHandler::Update(const QList<QString> &id, const QPair<QString, QString> field_value)
{
    if(id.size() == 0)
        return false;
    unsigned int _id = id[0].toUInt();
    QString field = field_value.first;
    if(field!="name")
        return false;
    QString new_name = field_value.second;
    return dim.SetDepartmentName(_id,new_name);
}

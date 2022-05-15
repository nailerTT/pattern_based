#include "staff.h"

staff::Staff::Staff(int staffid, int deptid, QString name)
    :_staff_id(staffid),_dept_id(deptid),_staff_name(name)
{

}

int staff::Staff::GetStaffID() const
{
    return this->_staff_id;
}

int staff::Staff::GetDeptID() const
{
    return this->_dept_id;
}

QString staff::Staff::GetName() const
{
    return this->_staff_name;
}

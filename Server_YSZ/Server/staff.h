#ifndef STAFF_H
#define STAFF_H
#include "QString"
namespace staff{
    class Staff
    {
    public:
        Staff(int staffid,int deptid,QString name);
        int GetStaffID() const;
        int GetDeptID() const;
        QString GetName() const;
    private:
        int _staff_id;
        int _dept_id;
        QString _staff_name;

    };
}


#endif // STAFF_H

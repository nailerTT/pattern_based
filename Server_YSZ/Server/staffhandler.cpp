#include "staffhandler.h"

StaffHandler::StaffHandler()
    :cs("coursecnn_cs"+QString::number(GetANewId()),"staffcoursecnn_cs"+QString::number(GetANewId()),"staffcnn_cs"+QString::number(GetANewId())),
      sif("shcnn"+QString::number(GetANewId())),
      ls("shcnn_ls"+QString::number(GetANewId()),"shcnn_ls"+QString::number(GetANewId()),
         "shcnn_ls"+QString::number(GetANewId()),"shcnn_ls"+QString::number(GetANewId())),
      as("shcnncnn_as"+QString::number(GetANewId()),"shcnncnn_as"+QString::number(GetANewId()),"shcnncnn_as"+QString::number(GetANewId()))
{

}

bool StaffHandler::Get(const QList<QString> &ids, const QString &property, QString &ref)
{
    unsigned int staffid = ids[0].toUInt();
    if(property == "password")
        return sif.GetPassword(staffid,ref);
    else if(property == "name")
        return sif.GetName(staffid,ref);
    else if(property == "state")
        return sif.GetRegisterStatus(staffid,ref);
    else if(property == "departmentid")
        return sif.GetDepartment(staffid,ref);
    else if(property == "sentletterids")
    {
        QList<unsigned int> list;

        if(ls.FetchSentLetters(staffid,list))
        {
            for(int i=0;i<list.size()-1;i++)
                ref.append(QString::number(list[i])+",");
            ref.append(QString::number(list[list.size()-1]));
        }
        else return false;
    }
    else if(property == "receivedletterids")
    {
        QList<unsigned int> list;
        if(ls.FetchReceivedLetters(staffid,list))
        {
            for(int i=0;i<list.size()-1;i++)
                ref.append(QString::number(list[i])+",");
            ref.append(QString::number(list[list.size()-1]));
        }
        else return false;
    }
    else if(property == "enrolledcourseids")
    {
        QList<unsigned int> list;
        if(cs.GetEnrolledCourses(staffid,list))
        {
            for(int i=0;i<list.size()-1;i++)
            {
                ref.append(QString::number(list[i])+",");
            }
            ref.append(QString::number(list[list.size()-1]));
        }
        else return false;
    }
    else if(property == "taughtcourseids")
    {
        QList<unsigned int> list;
        if(cs.GetTaughtCourses(staffid,list))
        {
            for(int i=0;i<list.size()-1;i++)
            {
                ref.append(QString::number(list[i]));
            }
            ref.append(QString::number(list[list.size()-1]));
        }
        else return false;
    }
    else if(property == "taughtcourseids")
    {
        QList<unsigned int> list;
        if(as.GetActivitiesAsParticipant(staffid,list))
        {
            for(int i=0;i<list.size()-1;i++)
            {
                ref.append(QString::number(list[i]));
            }
            ref.append(QString::number(list[list.size()-1]));
        }
        else return false;
    }
    else{
        return false;
    }
}

bool StaffHandler::ADD(const QList<QString> &values, QString &ref)
{
    QString name = values[0];
    QString state = values[1];
    RegisterState rstate;
    if(state == "Fully Registered")
        rstate = RegisterState::Full;
    else if(state == "Pending Registered")
        rstate = RegisterState::Pending;
    else
        rstate = RegisterState::Not;
    QString deptid = values[2];
    QString role = values[3];
    bool gender = values[4].toLower() == "male";
    QString password = values[5];
    if(values[4]=="student")
    {
        return sif.AddNewStudent(name,deptid.toUInt(),gender,rstate,password);
    }
    else
        return sif.AddNewStaff(name,deptid.toUInt(),gender,password);
}

bool StaffHandler::Del(const QList<QString> &id)
{
    if(id.size()==0)
        return false;
    unsigned int _id = id[0].toUInt();
    if(sif.DelStaff(_id))
    {
        //送信者删除
        ls.DeleteSender(_id);
        //收信者删除
        ls.DeleteReceiver(_id);
        //课程里面的staff也要删除
        cs.DelAStaff(_id);
        return true;
    }
    else return false;
}

bool StaffHandler::Update(const QList<QString> &id, const QPair<QString, QString> field_value)
{
    unsigned int _id = id[0].toUInt();
    QString field = field_value.first;
    QString value = field_value.second;
    if(field == "password")
    {
        return sif.SetPassword(_id,value);
    }
    else if(field == "name")
    {
        return sif.SetName(_id,value);
    }
    else if(field == "departmentid")
    {
        return sif.SetDepartment(_id,value.toUInt());
    }
    else if(field == "state")
    {
        RegisterState state;
        if(value == "Fully Registered")
            state = RegisterState::Full;
        else if(value == "Pending Registered")
            state = RegisterState::Pending;
        else
            state = RegisterState::Not;
        return sif.SetStaffState(_id,state);
    }
}

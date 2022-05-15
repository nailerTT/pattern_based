#include "activityhandler.h"

AcitivityHandler::AcitivityHandler()
    :as("ahcnn_as"+QString::number(GetANewId()),"ahcnn_as"+QString::number(GetANewId()),"ahcnn_as"+QString::number(GetANewId()))
{

}

bool AcitivityHandler::Get(const QList<QString> &ids, const QString &property, QString &ref)
{
    if(ids.size()==0)
        return false;
    unsigned int activityid = ids[0].toUInt();
    if(property == "name")
    {
        return as.GetActivityName(activityid,ref);
    }
    else if(property == "time")
    {
        return as.GetActivityTime(activityid,ref);
    }
    else if(property == "location")
    {
        return as.GetActivityLocation(activityid,ref);
    }
    else if(property == "link")
    {
        return as.GetActivityLink(activityid,ref);
    }
    else
        return false;
}

bool AcitivityHandler::ADD(const QList<QString> &values, QString &ref)
{
    //name,time,location,link
    if(values.size() == 4)
    {
        QString name = values[0];
        QString time = values[1];
        QString location = values[2];
        QString link = values[3];
        return as.NewActivity(name,time,location,link,-1);
    }
    //activityid,staffid,role
    else if(values.size() == 3)
    {
        unsigned int activityid = values[0].toUInt();
        unsigned int staffid = values[1].toUInt();
        QString role = values[2];
        if(role == "participant")
            return as.Subscribe(staffid,activityid);
        else if(role == "host")
            return as.SetHost(activityid,staffid);
        else return false;
    }
    else return false;
}

bool AcitivityHandler::Del(const QList<QString> &id)
{
    //Del,activity,activityid
    //QuitActivity,activityid,staffid
    if(id.size()!=3)
    {
        return false;
    }
    if(id.at(0)=="Del")
    {
        unsigned int activityid = id[2].toUInt();
        return as.DelAnActivity(activityid);
    }
    else if(id.at(0)=="QuitActivity")
    {
        unsigned int activityid = id[1].toUInt();
        unsigned int staffid = id[2].toUInt();
        return as.Quit(staffid,activityid);
    }
    else return false;
}

bool AcitivityHandler::Update(const QList<QString> &id, const QPair<QString, QString> field_value)
{
    if(id.size() == 0)
        return false;
    unsigned int activityid = id[0].toUInt();
    QString field = field_value.first;
    QString value = field_value.second;
    if(field == "name")
    {
        return as.SetActivityName(activityid,value);
    }
    else if(field == "time")
    {
        return as.SetActivityTime(activityid,value);
    }
    else if(field == "location")
    {
        return as.SetActivityLocation(activityid,value);
    }
    else if(field == "link")
    {
        return as.SetActivityLink(activityid,value);
    }
    else
        return false;
}

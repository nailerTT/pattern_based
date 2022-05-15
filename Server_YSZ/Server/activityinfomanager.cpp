#include "activityinfomanager.h"

ActivityInfoManager::ActivityInfoManager(const QString &connection_name)
    :InfoManager(connection_name)
{

}

bool ActivityInfoManager::AddActivity(const QString name, const QString time, const QString location, const QString link)
{
    QString _name = "'" + name +"'";
    QString _time = "str_to_date( '"+time+"','%Y-%m-%d %H:%i:%s')";
    QString _loc = "'" + location+"'";
    QString _link = "'"+link+"'";
    return ddba.Add("activity",{"activityname","activitytime","location","link"},{_name,_time,_loc,_link});
}

bool ActivityInfoManager::DelActivity(const unsigned int id)
{
    return ddba.Del("activity",{"activityid="+QString::number(id)});
}

bool ActivityInfoManager::GetActivityName(const unsigned int id, QString &name)
{
    QString s = "activityname";
    return GetInfo(id,name,s);
}

bool ActivityInfoManager::GetLocation(const unsigned int id, QString &location)
{
    QString s = "location";
    return GetInfo(id,location,s);
}

bool ActivityInfoManager::GetTime(const unsigned int id, QString &time)
{
    QString _date = "date_format(activitytime, '%Y-%m-%d %H:%i:%s')";
    return GetInfo(id,time,_date);
}

bool ActivityInfoManager::GetLink(const unsigned int id, QString &link)
{
    QString s = "link";
    return GetInfo(id,link,s);
}

bool ActivityInfoManager::ReSetLink(const unsigned int id, const QString &link)
{
    QString _link = "'"+link+"'";
    return ddba.Mod("activity",{"activityid="+QString::number(id)},{"link"},{_link});
}

bool ActivityInfoManager::ReSetAddress(const unsigned int id, const QString &addr)
{
    QString _addr = "'" + addr +"'";
    return ddba.Mod("activity",{"activityid="+QString::number(id)},{"location"},{_addr});
}

bool ActivityInfoManager::ReSetTime(const unsigned int id, const QString &time)
{
    QString _date = "str_to_date( '"+time+"','%Y-%m-%d %H:%i:%s')";
    return ddba.Mod("activity",{"activityid="+QString::number(id)},{"activitytime"},{_date});
}

bool ActivityInfoManager::ReSetName(const unsigned int id, const QString &name)
{
    QString _name = "'"+name+"'";
    return ddba.Mod("activity",{"activityid="+QString::number(id)},{"activityname"},{_name});
}

bool ActivityInfoManager::GetAllActivityNames(QList<QString> &name)
{
    QString s = "activityname";
    return GetAllInfo(s,name);
}

bool ActivityInfoManager::GetAllActivityLocations(QList<QString> &locs)
{
    QString s = "location";
    return GetAllInfo(s,locs);
}

bool ActivityInfoManager::GetAllActivityTime(QList<QString> &dates)
{
    QString s = "activitytime";
    return GetAllInfo(s,dates);
}

bool ActivityInfoManager::GetAllActivityLinks(QList<QString> &links)
{
    QString s = "link";
    return GetAllInfo(s,links);
}

bool ActivityInfoManager::GetInfo(const unsigned int id, QString &info, QString &fieldname)
{
    if(ddba.Ask("activity",{"activityid="+QString::number(id)},{fieldname}))
    {
        if(ddba.HasNext()==false)
        {
            info = "nu such an activity";
            return false;
        }
        info = ddba.FetchNextRow()[0];
        return true;
    }
    else{
        info = "database access fail";
        return false;
    }
}

bool ActivityInfoManager::GetAllInfo(QString &fieldname,QList<QString>& ans)
{
    if(ddba.Ask("activity",{},{fieldname}))
    {
        while(ddba.HasNext())
        {
            ans.append(ddba.FetchNextRow()[0]);
        }
        return true;
    }
    else{
        return false;
    }
}

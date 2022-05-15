#include "activitysubscribinfomanager.h"

ActivitySubscribInfoManager::ActivitySubscribInfoManager(const QString &connection_name)
    :InfoManager(connection_name)
{

}

bool ActivitySubscribInfoManager::Subscribe(const unsigned int staffid, const unsigned int activityid)
{
    return ddba.Add("subscribeactivity",{"activityid","staffid","stafftype"},
                    {QString::number(activityid),QString::number(staffid),"'participant'"});
}

bool ActivitySubscribInfoManager::DelActivity(const unsigned int activityid)
{
    return ddba.Del("subscribeactivity",{"activityid="+QString::number(activityid)});
}

bool ActivitySubscribInfoManager::Host(const unsigned int staffid, const unsigned int activityid)
{
    return ddba.Add("subscribeactivity",{"activityid","staffid","stafftype"},
                    {QString::number(activityid),QString::number(staffid),"'host'"});
}

bool ActivitySubscribInfoManager::GetHost(const unsigned int activityid, unsigned int &staffid)
{
    if(ddba.Ask("subscribeactivity",{"activityid="+QString::number(activityid),"stafftype='host'"},{"staffid"}))
    {
        if(ddba.HasNext()==false)
            return false;
        staffid = ddba.FetchNextRow()[0].toUInt();
    }
    else{
        return false;
    }
}

bool ActivitySubscribInfoManager::Quit(const unsigned int staffid, const unsigned int activityid)
{
    return ddba.Del("subscribeactivity",{"activityid="+QString::number(activityid),
                                         "staffid="+QString::number(staffid)});
}

bool ActivitySubscribInfoManager::JoinedActivities(const unsigned int staffid, QList<unsigned int> &activities)
{
    if(ddba.Ask("subscribeactivity",{"staffid="+QString::number(staffid)},{"activityid"}))
    {
        if(ddba.HasNext()==false)
            return false;
        while(ddba.HasNext())
        {
            activities.append(ddba.FetchNextRow()[0].toUInt());
        }
        return true;
    }
    else{
        return false;
    }
}

bool ActivitySubscribInfoManager::HostedActivities(const unsigned int staffid, QList<unsigned int> &activities)
{
    if(ddba.Ask("subscribeactivity",{"staffid="+QString::number(staffid),"stafftype='host'"},{"activityid"}))
    {
        if(ddba.HasNext()==false)
            return false;
        while(ddba.HasNext())
        {
            activities.append(ddba.FetchNextRow()[0].toUInt());
        }
        return true;
    }
    else{
        return false;
    }
}

bool ActivitySubscribInfoManager::GetParticipants(const unsigned int activityID, QList<unsigned int> &staffs)
{
    if(ddba.Ask("subscribeactivity",{"activityid="+QString::number(activityID)},{"staffid"}))
    {
        if(ddba.HasNext()==false)
            return false;
        while(ddba.HasNext())
        {
            staffs.append(ddba.FetchNextRow()[0].toUInt());
        }
        return true;
    }
    else{
        return false;
    }
}

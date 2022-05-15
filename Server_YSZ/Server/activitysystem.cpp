#include "activitysystem.h"

ActivitySystem::ActivitySystem(const QString aim_cnn, const QString sim_cnn,const QString asim_cnn)
    : InfoManager(""),aim(aim_cnn),sim(sim_cnn),asim(asim_cnn)
{

}

bool ActivitySystem::NewActivity(const QString &name, const QString &time, const QString &location, const QString &link, const unsigned int hostid)
{
    if(this->aim.AddActivity(name,time,location,link))
    {
        unsigned int id = aim.GetLastInsertID();
        asim.Host(hostid,id);
        return true;
    }
    else
        return false;
}

bool ActivitySystem::Subscribe(const unsigned int staffid,const unsigned int activityid)
{
    return asim.Subscribe(staffid,activityid);
}

bool ActivitySystem::Quit(const unsigned int staffid, const unsigned int activityid)
{
    return asim.Quit(staffid,activityid);
}

bool ActivitySystem::SetHost(const unsigned int activityid, const unsigned int staffid)
{
    return asim.Host(staffid,activityid);
}

bool ActivitySystem::GetActivityName(const unsigned int activityid, QString &name)
{
    return aim.GetActivityName(activityid,name);
}

bool ActivitySystem::GetActivityLocation(const unsigned int activityid, QString &loc)
{
    return aim.GetLocation(activityid,loc);
}

bool ActivitySystem::GetActivityLink(const unsigned int activityid, QString &link)
{
    return aim.GetLink(activityid,link);
}

bool ActivitySystem::GetActivityTime(const unsigned int activityid, QString &time)
{
    return aim.GetTime(activityid,time);
}

bool ActivitySystem::SetActivityName(const unsigned int activityid, const QString &name)
{
    return aim.ReSetName(activityid,name);
}

bool ActivitySystem::SetActivityLocation(const unsigned int activityid, const QString &loc)
{
    return aim.ReSetAddress(activityid,loc);
}

bool ActivitySystem::SetActivityLink(const unsigned int activityid, const QString &link)
{
    return aim.ReSetLink(activityid,link);
}

bool ActivitySystem::SetActivityTime(const unsigned int activityid, const QString &time)
{
    return aim.ReSetTime(activityid,time);
}

bool ActivitySystem::GetActivitiesAsParticipant(const unsigned int staffid, QList<unsigned int> activities)
{
    return asim.JoinedActivities(staffid,activities);
}

bool ActivitySystem::GetActivitiesAsHost(const unsigned int staffid, QList<unsigned int> activities)
{
    return asim.HostedActivities(staffid,activities);
}

bool ActivitySystem::DelAnActivity(const unsigned int activityid)
{
    return asim.DelActivity(activityid) && aim.DelActivity(activityid);
}

bool ActivitySystem::GetAllActivityInfo(QList<QString> &names, QList<QString> &locs, QList<QString> &dates, QList<QString> links)
{
    return aim.GetAllActivityNames(names)&&
           aim.GetAllActivityLocations(locs)&&
           aim.GetAllActivityTime(dates) &&
           aim.GetAllActivityLinks(links);
}


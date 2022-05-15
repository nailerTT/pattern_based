#ifndef ACTIVITYSUBSCRIBINFOMANAGER_H
#define ACTIVITYSUBSCRIBINFOMANAGER_H

#include "infomanager.h"

class ActivitySubscribInfoManager : public InfoManager
{
    Q_OBJECT
public:
    ActivitySubscribInfoManager(const QString& connection_name);
    bool Subscribe(const unsigned int staffid,const unsigned int activityid);
    bool DelActivity(const unsigned int activityid);
    bool Host(const unsigned int staffid,const unsigned int activityid);
    bool GetHost(const unsigned int activityid,unsigned int& staffid);
    bool Quit(const unsigned int staffid, const unsigned int activityid);
    bool JoinedActivities(const unsigned int staffid,QList<unsigned int>& activities);
    bool HostedActivities(const unsigned int staffid,QList<unsigned int>& activities);
    bool GetParticipants(const unsigned int activityID,QList<unsigned int>& staffs);
};

#endif // ACTIVITYSUBSCRIBINFOMANAGER_H

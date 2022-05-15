#ifndef ACTIVITYSYSTEM_H
#define ACTIVITYSYSTEM_H

#include <QObject>
#include "activityinfomanager.h"
#include "staffinfomanager.h"
#include "activitysubscribinfomanager.h"

class ActivitySystem : public InfoManager
{
    Q_OBJECT
public:
    explicit ActivitySystem(const QString aim_cnn = "aimcnn_as",const QString sim_cnn = "simcnn_as",const QString asim_cnn = "asimcnn_as");
    bool NewActivity(const QString& name,const QString& time,const QString& location,const QString& link,const unsigned int hostid);
    bool Subscribe(const unsigned int staffid, const unsigned int activityid);
    bool Quit(const unsigned int staffid,const unsigned int activityid);
    bool SetHost(const unsigned int activityid,const unsigned int staffid);
    bool GetActivityName(const unsigned int activityid,QString& name);
    bool GetActivityLocation(const unsigned int activityid,QString& loc);
    bool GetActivityLink(const unsigned int activityid,QString& link);
    bool GetActivityTime(const unsigned int activityid,QString& time);
    bool SetActivityName(const unsigned int activityid,const QString& name);
    bool SetActivityLocation(const unsigned int activityid,const QString& loc);
    bool SetActivityLink(const unsigned int activityid,const QString& link);
    bool SetActivityTime(const unsigned int activityid,const QString& time);
    bool GetActivitiesAsParticipant(const unsigned int staffid,QList<unsigned int> activities);
    bool GetActivitiesAsHost(const unsigned int staffid,QList<unsigned int>activities);
    bool DelAnActivity(const unsigned int activityid);
    bool GetAllActivityInfo(QList<QString>& names,QList<QString>& locs,QList<QString>& dates,QList<QString>links);
signals:
private:
    ActivityInfoManager aim;
    StaffInfoManager sim;
    ActivitySubscribInfoManager asim;
};

#endif // ACTIVITYSYSTEM_H

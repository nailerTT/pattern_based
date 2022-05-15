#ifndef ACTIVITYINFOMANAGER_H
#define ACTIVITYINFOMANAGER_H

#include "infomanager.h"

class ActivityInfoManager : public InfoManager
{
    Q_OBJECT
public:
    ActivityInfoManager(const QString& connection_name);
    bool AddActivity(const QString name,const QString time,const QString location,const QString link);
    bool DelActivity(const unsigned int id);
    bool GetActivityName(const unsigned int id,QString& name);
    bool GetLocation(const unsigned int id,QString& location);
    bool GetTime(const unsigned int id,QString& time);
    bool GetLink(const unsigned int id,QString& link);
    bool ReSetLink(const unsigned int id,const QString& link);
    bool ReSetAddress(const unsigned int id, const QString& addr);
    bool ReSetTime(const unsigned int id,const QString& time);
    bool ReSetName(const unsigned int id,const QString& name);
    bool GetAllActivityNames(QList<QString>&name);
    bool GetAllActivityLocations(QList<QString>& locs);
    bool GetAllActivityTime(QList<QString>& dates);
    bool GetAllActivityLinks(QList<QString>& links);
private:
    bool GetInfo(const unsigned int id,QString& info,QString& fieldname);
    bool GetAllInfo(QString& fieldname, QList<QString> &ans);
};

#endif // ACTIVITYINFOMANAGER_H

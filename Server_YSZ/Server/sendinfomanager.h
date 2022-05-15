#ifndef SENDINFOMANAGER_H
#define SENDINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
class SendInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit SendInfoManager(QString cn);
    ~SendInfoManager();
    bool AddRecord(const unsigned int staffid,const unsigned int letterid,const QString date);
    bool DelRecord(const unsigned int staffid,const unsigned int letterid);
    bool GetSentLetterIds(const unsigned int staffid,QList<unsigned int>& ids);
    bool GetSentDate(const unsigned int staffid, const unsigned int letterid,QString& date);
    //date's format: 'year-mon-day[ h:m:s]'
    bool GetSentLetterIdAtDay(const unsigned int staffid, const QString& date, unsigned int& id);
    bool GetSenderId(const unsigned int letterid,unsigned int& senderId);
    bool CheckALetterIsUnderSender(const unsigned int letterid, bool &res);
signals:
};

#endif // SENDINFOMANAGER_H

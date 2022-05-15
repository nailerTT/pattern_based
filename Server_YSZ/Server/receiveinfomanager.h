#ifndef RECEIVEINFOMANAGER_H
#define RECEIVEINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
class ReceiveInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit ReceiveInfoManager(QString cn);
    ~ReceiveInfoManager();
    bool AddRecord(unsigned int staffid,unsigned int letterid);
    bool DelRecord(unsigned int staffid,unsigned int letterid);
    bool GetReceivedLettersID(unsigned int staffid,QList<unsigned int>& ids);
    bool GetReceiversID(unsigned int letterid,QList<unsigned int>& ids);
    bool CheckALetterIsUnderReceive(const unsigned int letterid,bool& res);
signals:
};

#endif // RECEIVEINFOMANAGER_H

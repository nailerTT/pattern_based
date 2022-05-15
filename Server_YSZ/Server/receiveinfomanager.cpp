#include "receiveinfomanager.h"

ReceiveInfoManager::ReceiveInfoManager(QString cn)
    :InfoManager(cn)
{

}

ReceiveInfoManager::~ReceiveInfoManager()
{

}

bool ReceiveInfoManager::AddRecord(unsigned int staffid, unsigned int letterid)
{
    return ddba.Add("receive",{"Staff_StaffID","Letter_LetterID"},{QString::number(staffid),QString::number(letterid)});
}

bool ReceiveInfoManager::DelRecord(unsigned int staffid, unsigned int letterid)
{
    return ddba.Del("receive",{"Staff_StaffID="+QString::number(staffid),"Letter_LetterID="+QString::number(letterid)});
}

bool ReceiveInfoManager::GetReceivedLettersID(unsigned int staffid, QList<unsigned int> &ids)
{
    if(ddba.Ask("receive",{"Staff_StaffID="+QString::number(staffid)},{"Letter_LetterID"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        else{
            while(ddba.HasNext())
            {
                ids.append(ddba.FetchNextRow()[0].toUInt());
            }
            return true;
        }
    }
    else{
        return false;
    }
}

bool ReceiveInfoManager::GetReceiversID(unsigned int letterid, QList<unsigned int> &ids)
{
    if(ddba.Ask("receive",{"Letter_LetterID="+QString::number(letterid)},{"Staff_StaffID"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        else{
            while(ddba.HasNext())
            {
                ids.append(ddba.FetchNextRow()[0].toUInt());
            }
            return true;
        }
    }
    else{
        return false;
    }
}

bool ReceiveInfoManager::CheckALetterIsUnderReceive(const unsigned int letterid, bool &res)
{
    if(ddba.Ask("receive",{"Letter_LetterID="+QString::number(letterid)},{"*"}))
    {
        res = ddba.HasNext();
        return true;
    }
    else{
        res = false;
        return false;
    }
}

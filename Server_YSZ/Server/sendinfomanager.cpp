#include "sendinfomanager.h"

SendInfoManager::SendInfoManager(QString cn)
    :InfoManager(cn)
{

}

SendInfoManager::~SendInfoManager()
{
}

bool SendInfoManager::AddRecord(const unsigned int staffid, const unsigned int letterid, const QString date)
{
    QString _date = "str_to_date( '"+date+"','%Y-%m-%d %H:%i:%s')";
    return ddba.Add("send",{"Student_StudentID","Letter_LetterID","date"},{QString::number(staffid),QString::number(letterid),_date});
}

bool SendInfoManager::DelRecord(const unsigned int staffid, const unsigned int letterid)
{
    return ddba.Del("send",{"Student_StudentID="+QString::number(staffid),"Letter_LetterID="+QString::number(letterid)});
}

bool SendInfoManager::GetSentLetterIds(const unsigned int staffid, QList<unsigned int> &ids)
{
    if(ddba.Ask("send",{"Student_StudentID="+QString::number(staffid)},{"Letter_LetterID"}))
    {
        if(ddba.HasNext()==false)
        {
            return false;
        }
        while(ddba.HasNext())
        {
            auto row = ddba.FetchNextRow();
            ids.append(row[0].toUInt());
        }
        return true;
    }
    else{
        return false;
    }
}

bool SendInfoManager::GetSentDate(const unsigned int staffid, const unsigned int letterid, QString &date)
{
    QString _date = "date_format(date, '%Y-%m-%d %H:%i:%s')";
    if(ddba.Ask("send",{"Student_StudentID="+QString::number(staffid),"Letter_LetterID="+QString::number(letterid)},{_date}))
    {
        if(ddba.HasNext() == false)
        {
            date = "no such send record";
            return false;
        }
        date = ddba.FetchNextRow()[0];
        return true;
    }
    else{
        date = ddba.FetchErrorMSG();
        return false;
    }
}

bool SendInfoManager::GetSentLetterIdAtDay(const unsigned int staffid, const QString &date, unsigned int &id)
{
    int idx = date.lastIndexOf("-");
    int space = date.indexOf(" ");
    unsigned int day;
    if(space == -1)
    {
        day = date.mid(idx+1).toUInt();
    }
    else{
        day = date.mid(idx+1,space-1-idx).toUInt();
    }
    if(ddba.Ask("send",{"day(date)="+QString::number(day),"Student_StudentID="+QString::number(staffid)},{"Letter_LetterID"}))
    {
        if(ddba.HasNext() == false)
        {
            id = -1;
            return false;
        }
        id = ddba.FetchNextRow()[0].toUInt();
        return true;
    }
    else{
        id = -1;
        return false;
    }
}

bool SendInfoManager::GetSenderId(const unsigned int letterid, unsigned int &senderId)
{
    if(ddba.Ask("send",{"Letter_LetterID="+QString::number(letterid)},{"Student_StudentID"}))
    {
        if(ddba.HasNext()==false)
            return false;
        senderId = ddba.FetchNextRow()[0].toUInt();
        return true;
    }
    else{
        return false;
    }
}

bool SendInfoManager::CheckALetterIsUnderSender(const unsigned int letterid,bool& res)
{
    if(ddba.Ask("send",{"Letter_LetterID="+QString::number(letterid)},{"*"}))
    {
        res = ddba.HasNext();
        return true;
    }
    else{
        res = false;
    }
}

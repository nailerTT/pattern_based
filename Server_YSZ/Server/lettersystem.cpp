#include "lettersystem.h"

LetterSystem::LetterSystem(const QString &staff_cnn, const QString &letter_cnn, const QString &receive_cnn, const QString &send_cnn)
    : InfoManager(""),sim(staff_cnn),lim(letter_cnn),rim(receive_cnn),sendim(send_cnn)
{

}

bool LetterSystem::FetchSentLetterTitles(const unsigned int staffid, QList<QString> &titles)
{
    QList<unsigned int> letter_ids;
    if(FetchSentLetters(staffid,letter_ids)==false)
    {
        return false;
    }
    bool flag = true;
    for(int i=0;i<letter_ids.size();i++)
    {
        QString title;
        flag = lim.GetTitle(letter_ids[i],title);
        if(flag == false)
            break;
        titles.append(title);
    }
    return flag;
}

bool LetterSystem::FetchReceivedLetterTitles(const unsigned int staffid, QList<QString> &titles)
{
    QList<unsigned int> letter_ids;
    if(FetchReceivedLetters(staffid,letter_ids))
    {
        bool flag = true;
        for(int i=0;i<letter_ids.size();i++)
        {
            QString title;
            flag = lim.GetTitle(letter_ids[i],title);
            if(flag == false)
                break;
            titles.append(title);
        }
        return flag;
    }
    else{
        return false;
    }
}

bool LetterSystem::FetchALetterSender(const unsigned int letterid, QString &sender)
{
    unsigned int staffid;
    if(sendim.GetSenderId(letterid,staffid)==false)
        return false;
    else{
        return sim.GetName(staffid,sender);
    }
}

bool LetterSystem::FetchALetterReceiver(const unsigned int letterid, QList<QString> &receiver)
{
    QList<unsigned int> staffids;
    if(rim.GetReceiversID(letterid,staffids))
    {
        for(int i=0;i<staffids.size();i++)
        {
            QString name;
            if(sim.GetName(staffids[i],name))
            {
                receiver.append(name);
            }
            else{
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool LetterSystem::FetchALetterContent(const unsigned int letterid, QString &content)
{
    return lim.GetLetterContent(letterid,content);
}

bool LetterSystem::FetchALetterState(const unsigned int letterid, LetterState &state)
{
    return lim.GetLetterState(letterid,state);
}

bool LetterSystem::FetchALetterTitle(const unsigned int letterid, QString &title)
{
    return lim.GetTitle(letterid,title);
}

bool LetterSystem::StarALetter(const unsigned int letterid)
{
    return lim.UpdateLetterState(letterid,LetterState::Star);
}

bool LetterSystem::ReadALetter(const unsigned int letterid)
{
    return lim.UpdateLetterState(letterid,LetterState::Read);
}

bool LetterSystem::UnreadALetter(const unsigned int letterid)
{
    return lim.UpdateLetterState(letterid,LetterState::NotRead);
}

bool LetterSystem::SendALetter
(const unsigned int sender, const unsigned int receiver, const QString &content,const QString&title, const QString datetime)
{
    if(lim.AddLetter(content,title,LetterState::NotRead))
    {
        unsigned int letterid = lim.GetLastInsertID();
        if(sendim.AddRecord(sender,letterid,datetime))
        {
            if(rim.AddRecord(receiver,letterid))
            {
                return true;
            }
            else{
                sendim.DelRecord(sender,letterid);
                lim.DelLetter(letterid);
                return false;
            }
        }
        else{
            lim.DelLetter(letterid);
            return false;
        }
    }
    else{
        return false;
    }
}

bool LetterSystem::DeleteALetterAsASender(const unsigned int letterid, const unsigned int staffid)
{
    if(sendim.DelRecord(staffid,letterid))
    {
        bool check;
        if(rim.CheckALetterIsUnderReceive(letterid,check))
        {
            if(check==false)
            {
                lim.DelLetter(letterid);
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool LetterSystem::DeleteALetterAsAReceiver(const unsigned int letterid, const unsigned int staffid)
{
    if(rim.DelRecord(staffid,letterid))
    {
        bool check;
        if(sendim.CheckALetterIsUnderSender(letterid,check))
        {
            if(!check)
                lim.DelLetter(letterid);
        }
        return true;
    }
    else{
        return false;
    }
}

bool LetterSystem::DeleteSender(const unsigned int senderid)
{
    QList<unsigned int> ids;
    if(FetchSentLetters(senderid,ids))
    {
        for(int i=0;i<ids.size();i++)
        {
            DeleteALetterAsASender(ids[i],senderid);
        }
        return true;
    }
    else
        return false;
}

bool LetterSystem::DeleteReceiver(const unsigned int receiverid)
{
    QList<unsigned int> ids;
    if(FetchReceivedLetters(receiverid,ids))
    {
        for(int i=0;i<ids.size();i++)
        {
            DeleteALetterAsAReceiver(ids[i],receiverid);
        }
        return true;
    }
    else
        return false;
}

bool LetterSystem::FetchSentLetters(const unsigned int staffid, QList<unsigned int>& letterids)
{
    return sendim.GetSentLetterIds(staffid,letterids);
}

bool LetterSystem::FetchReceivedLetters(const unsigned int staffid, QList<unsigned int> &letterids)
{
    return rim.GetReceivedLettersID(staffid,letterids);
}

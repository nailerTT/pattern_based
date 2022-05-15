#include "letterhandler.h"

Letterhandler::Letterhandler()
    :ls("staffcnn_ls"+QString::number(GetANewId()),"lettercnn_ls"+QString::number(GetANewId()),
        "receivecnn_ls"+QString::number(GetANewId()),"sendcnn_ls"+QString::number(GetANewId()))
{

}

bool Letterhandler::Get(const QList<QString> &ids, const QString &property, QString &ref)
{
    unsigned int id = ids[0].toUInt();
    if(property == "state")
    {
        LetterState state;
        if(ls.FetchALetterState(id,state))
        {
            switch(state){
            case LetterState::NotRead:
            default:
                ref = "not read";break;
            case LetterState::Read:
                ref = "read";break;
            case LetterState::Star:
                ref = "star";
            }
            return true;
        }
        else return false;
    }
    else if(property == "title")
    {
        return ls.FetchALetterTitle(id,ref);
    }
    else if(property == "content")
    {
        return ls.FetchALetterContent(id,ref);
    }
    else return false;
}

bool Letterhandler::ADD(const QList<QString> &values, QString &)
{
    QString sender = values[0];
    QString receiver = values[1];
    QString content = values[2];
    QString title = values[3];
    QString date = values[4];
    return ls.SendALetter(sender.toUInt(),receiver.toUInt(),content,title,date);
}

bool Letterhandler::Del(const QList<QString> &id)
{
    QString role = id[0];
    unsigned int letterid = id[0].toUInt();
    unsigned int staffid = id[1].toUInt();

    if(role == "receive")
    {
        return ls.DeleteALetterAsAReceiver(letterid,staffid);
    }
    else if(role == "send")
        return ls.DeleteALetterAsASender(letterid,staffid);
}

bool Letterhandler::Update(const QList<QString> &id, const QPair<QString, QString> field_value)
{
    unsigned int _id = id[0].toUInt();
    QString field = field_value.first;
    if(field == "state")
    {
        QString state = field_value.second;
        LetterState _state;
        if(state == "Read")
        {
            _state = LetterState::Read;
            return ls.ReadALetter(_id);
        }
        else if(state == "NotRead")
        {
            _state = LetterState::NotRead;
            return ls.UnreadALetter(_id);
        }
        else if(state == "Star")
        {
            _state = LetterState::Star;
            return ls.StarALetter(_id);
        }
        else return false;
    }
    else{
        return false;
    }
}

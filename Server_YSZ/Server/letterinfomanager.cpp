#include "letterinfomanager.h"

LetterInfoManager::LetterInfoManager(QString cn)
    :InfoManager(cn)
{

}

bool LetterInfoManager::AddLetter(const QString &content, const QString title, LetterState state)
{
    QString _content = "'"+content+"'";
    QString _state;
    QString _title = "'"+title+"'";
    switch(state)
    {
    case LetterState::NotRead:
    default:
        _state = "'NotRead'";break;
    case LetterState::Read:
        _state = "'Read'";break;
    case LetterState::Star:
        _state = "'Star'";break;
    }

    return ddba.Add("letter",{"content","status","title"},{_content,_state,_title});
}

bool LetterInfoManager::DelLetter(const unsigned int id)
{
    return ddba.Del("letter",{"letterid="+QString::number(id)});
}

bool LetterInfoManager::GetLetterContent(const unsigned int id, QString& ans)
{
    if(ddba.Ask("letter",{"letterid="+QString::number(id)},{"content"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such letter with id=" + QString::number(id);
            return false;
        }
        else{
            ans = ddba.FetchNextRow()[0];
            return true;
        }
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

bool LetterInfoManager::GetLetterState(const unsigned int id, LetterState &state)
{
    if(ddba.Ask("letter",{"letterid="+QString::number(id)},{"status"}))
    {
        if(ddba.HasNext()==false)
        {
            state = LetterState::NotRead;
            return false;
        }
        else{
            QString ans = ddba.FetchNextRow()[0];
            if(ans.toLower() == "star")
                state = LetterState::Star;
            else if(ans.toLower() == "read")
                state = LetterState::Read;
            else
                state = LetterState::NotRead;
            return true;
        }
    }
    else{
        state = LetterState::NotRead;
        return false;
    }
}

bool LetterInfoManager::UpdateLetterState(const unsigned int id, LetterState new_state)
{
    QString _state;
    switch(new_state)
    {
    case LetterState::NotRead:
    default:
        _state = "'NotRead'";break;
    case LetterState::Read:
        _state = "'Read'";break;
    case LetterState::Star:
        _state = "'Star'";break;
    }
    return ddba.Mod("letter",{"letterid="+QString::number(id)},{"status"},{_state});
}

bool LetterInfoManager::GetTitle(const unsigned int id, QString &ans)
{
    if(ddba.Ask("letter",{"letterid="+QString::number(id)},{"title"}))
    {
        if(ddba.HasNext()==false)
        {
            ans = "no such letter with id=" + QString::number(id);
            return false;
        }
        else{
            ans = ddba.FetchNextRow()[0];
            return true;
        }
    }
    else{
        ans = ddba.FetchErrorMSG();
        return false;
    }
}

#ifndef LETTERINFOMANAGER_H
#define LETTERINFOMANAGER_H

#include <QObject>
#include "infomanager.h"
enum class LetterState{
    Read,NotRead,Star
};

class LetterInfoManager : public InfoManager
{
    Q_OBJECT
public:
    explicit LetterInfoManager(QString cn);
    ~LetterInfoManager(){}
    bool AddLetter(const QString& content, const QString title, LetterState state = LetterState::NotRead);
    bool DelLetter(const unsigned int id);
    bool GetLetterContent(const unsigned int id, QString &ans);
    bool GetLetterState(const unsigned int id, LetterState& state);
    bool UpdateLetterState(const unsigned int id, LetterState new_state);
    bool GetTitle(const unsigned int id,QString& ans);
signals:

};

#endif // LETTERINFOMANAGER_H

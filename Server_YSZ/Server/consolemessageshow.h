#ifndef CONSOLEMESSAGESHOW_H
#define CONSOLEMESSAGESHOW_H

#include "messageprint.h"

class ConsoleMessageShow : public MessagePrint
{
public:
    ConsoleMessageShow(Subject* subject = nullptr);
    void PrintMsg(QString msg);
    void PrintError(QString error);
    void Clear(){}
};

#endif // CONSOLEMESSAGESHOW_H

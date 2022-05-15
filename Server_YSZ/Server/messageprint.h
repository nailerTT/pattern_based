#ifndef MESSAGEPRINT_H
#define MESSAGEPRINT_H
#include "QString"
#include "observer.h"
class MessagePrint:public Observer
{
public:
    MessagePrint(Subject* subject = nullptr);
    bool Update(const QMap<QString,QString>& map);
    virtual void PrintMsg(QString msg) = 0;
    virtual void PrintError(QString error_msg) = 0;
    virtual void Clear() = 0;
    virtual ~MessagePrint(){}
};

#endif // MESSAGEPRINT_H

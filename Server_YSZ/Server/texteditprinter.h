#ifndef TEXTEDITPRINTER_H
#define TEXTEDITPRINTER_H

#include "messageprint.h"
#include "QTextEdit"
class TextEditPrinter : public MessagePrint
{
public:
    TextEditPrinter(Subject* sub = nullptr,QTextEdit* edit = new QTextEdit);
    virtual void PrintMsg(QString msg);
    virtual void PrintError(QString error_msg);
    void Clear();
private:
    QTextEdit* _edit;
};

#endif // TEXTEDITPRINTER_H

#ifndef LETTERHANDLER_H
#define LETTERHANDLER_H

#include "handler.h"
#include "lettersystem.h"


class Letterhandler : public Handler
{
    Q_OBJECT
public:
    Letterhandler();
    virtual bool Get(const QList<QString>& ids,const QString& property,QString& ref);
    virtual bool ADD(const QList<QString>& values,QString&ref);
    virtual bool Del(const QList<QString>& constrains);
    virtual bool Update(const QList<QString>& id,const QPair<QString,QString> field_value);
private:
    LetterSystem ls;
};

#endif // LETTERHANDLER_H

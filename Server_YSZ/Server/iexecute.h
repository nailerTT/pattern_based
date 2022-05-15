#ifndef IEXECUTE_H
#define IEXECUTE_H

#include <QObject>
#include <QString>
#include "visitor.h"

class Execute : public QObject
{
    Q_OBJECT
public:
    explicit Execute(QObject *parent = nullptr);
    virtual ~Execute();
    virtual QString execute(QString query);
signals:

};

#endif // IEXECUTE_H

#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QObject>
#include "decorateddatabaseaccess.h"
class InfoManager : public QObject
{
    Q_OBJECT
public:
    explicit InfoManager(QString connection_name);
    virtual ~InfoManager();
    void StartTransaction();
    void Commit();
    void Rollback(const QString& point);
    void SetRollbackPoint(const QString& point);
    unsigned int GetLastInsertID();
signals:
protected:
    DecoratedDatabaseAccess ddba;
};

#endif // INFOMANAGER_H

#include "infomanager.h"

InfoManager::InfoManager(QString connection_name)
    : QObject{nullptr},ddba(connection_name,new SqlDatabase("miniproject",connection_name,"root","19990807","localhost",3306))
{
    ddba.ConnectToDatabase();
}

InfoManager::~InfoManager()
{
    ddba.Disconnect();
}

void InfoManager::StartTransaction()
{
    ddba.StartTransaction();
}

void InfoManager::Commit()
{
    ddba.Commit();
}

void InfoManager::Rollback(const QString &point)
{
    ddba.Rollback(point);
}

void InfoManager::SetRollbackPoint(const QString &point)
{
    ddba.SetARollbackPoint(point);
}

unsigned int InfoManager::GetLastInsertID()
{
    QString id;
    ddba.GetLastInsertIndentification(id);
    return id.toUInt();
}

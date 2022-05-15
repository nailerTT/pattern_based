#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include "databaseaccess.h"
#include <QSqlDatabase>
class SqlDatabase : public DatabaseAccess
{
public:
    SqlDatabase(QString database_name,QString& connection_name,QString user_name, QString password,QString hostname,quint16 port);
    virtual bool ConnectToDatabase();
    virtual void Disconnect();
    virtual bool IsConnected() const;
    virtual bool Add(const QString storage,const QList<QString>& keys, const QList<QString> values);
    virtual bool Del(const QString storage,const QList<QString>& constrains);
    virtual bool Mod(const QString storage, const QList<QString>& constrains, const QList<QString> fields, const QList<QString> new_values);
    virtual bool Ask(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names) ;
    virtual bool Query(QString query);
    virtual bool Update(const QMap<QString,QString>& map);
    virtual QString FormView(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names);
    virtual void StartTransaction();
    virtual void Commit();
    virtual void Rollback(const QString& point);
    virtual void SetARollbackPoint(const QString& point);
    virtual void GetLastInsertIndentification(QString& id);
private:
    QString FormWhereClause(const QList<QString> &constrains);
    QSqlDatabase _database;
    QString _hostname;
    quint16 _port;
};

#endif // SQLDATABASE_H

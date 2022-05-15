#ifndef DECORATEDDATABASEACCESS_H
#define DECORATEDDATABASEACCESS_H

#include "sqldatabase.h"
#include "nulldatabase.h"
class DecoratedDatabaseAccess : public DatabaseAccess
{
public:
    DecoratedDatabaseAccess( QString &connectionname,DatabaseAccess* database = new NullDatabase);
    ~DecoratedDatabaseAccess();
    virtual bool ConnectToDatabase();
    virtual void Disconnect();
    virtual bool IsConnected() const;

    virtual bool Add(const QString storage,const QList<QString>& keys, const QList<QString> values);
    virtual bool Del(const QString storage,const QList<QString>& constrains);
    virtual bool Mod(const QString storage, const QList<QString>& constrains, const QList<QString> fields, const QList<QString> new_values);
    virtual bool Ask(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names);
    virtual bool Update(const QMap<QString, QString> &map);
    virtual QString FetchErrorMSG();
    virtual void ClearCach() { this->_database->ClearCach();}
    virtual bool HasNext() const {return this->_database->HasNext();}
    virtual QList<QString> FetchNextRow() {return this->_database->FetchNextRow();}
    virtual QString GetDatabaseName() const {return this->_database->GetDatabaseName();}
    virtual QString GetUserName() const {return this->_database->GetUserName();}
    virtual QString GetPassword() const {return this->_database->GetPassword();}
    virtual QString FormView(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names);
    virtual void StartTransaction();
    virtual void SetARollbackPoint(const QString& point);
    virtual void Commit();
    virtual void Rollback(const QString& point);
    virtual void GetLastInsertIndentification(QString& id);
private:
    DatabaseAccess* _database;
};

#endif // DECORATEDDATABASEACCESS_H

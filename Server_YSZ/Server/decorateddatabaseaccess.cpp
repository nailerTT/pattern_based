#include "decorateddatabaseaccess.h"

DecoratedDatabaseAccess::DecoratedDatabaseAccess(QString& connectionname,DatabaseAccess *database)
    :DatabaseAccess(database?database->GetDatabaseName():"",connectionname,database?database->GetUserName():"",database?database->GetPassword():""),_database(database)
{

}

DecoratedDatabaseAccess::~DecoratedDatabaseAccess()
{
    delete this->_database;
    this->_database = nullptr;
}

bool DecoratedDatabaseAccess::ConnectToDatabase()
{
    return this->_database->ConnectToDatabase();
}

void DecoratedDatabaseAccess::Disconnect()
{
    return this->_database->Disconnect();
}

bool DecoratedDatabaseAccess::IsConnected() const
{
    return this->_database->IsConnected();
}

bool DecoratedDatabaseAccess::Add(const QString storage, const QList<QString> &keys, const QList<QString> values)
{
    QList<QString> _keys(keys);
    QList<QString> _values(values);
    return this->_database->Add(storage,_keys,_values);
}

bool DecoratedDatabaseAccess::Del(const QString storage, const QList<QString> &keys)
{
    return this->_database->Del(storage,keys);
}

bool DecoratedDatabaseAccess::Mod(const QString storage, const QList<QString> &keys, const QList<QString> fields, const QList<QString> new_values)
{
    return this->_database->Mod(storage,keys,fields,new_values);
}

bool DecoratedDatabaseAccess::Ask(const QString storage, const QList<QString> &constrains, const QList<QString> &field_names)
{
    return this->_database->Ask(storage,constrains,field_names);
}

bool DecoratedDatabaseAccess::Update(const QMap<QString, QString>& map)
{
    return this->_database->Update(map);
}

QString DecoratedDatabaseAccess::FetchErrorMSG()
{
    return this->_database->FetchErrorMSG();
}

QString DecoratedDatabaseAccess::FormView(const QString storage, const QList<QString> &constrains, const QList<QString> &field_names)
{
    return this->_database->FormView(storage,constrains,field_names);
}

void DecoratedDatabaseAccess::StartTransaction()
{
    this->_database->StartTransaction();
}

void DecoratedDatabaseAccess::SetARollbackPoint(const QString &point)
{
    this->_database->SetARollbackPoint(point);
}

void DecoratedDatabaseAccess::Commit()
{
    this->_database->Commit();
}

void DecoratedDatabaseAccess::Rollback(const QString &point)
{
    this->_database->Rollback(point);
}

void DecoratedDatabaseAccess::GetLastInsertIndentification(QString &id)
{
    this->_database->GetLastInsertIndentification(id);
}


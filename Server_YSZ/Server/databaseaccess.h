#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include "observer.h"
#include <QList>
#include <QString>
#include <QMap>
class DatabaseAccess:public Observer
{
    Q_OBJECT
public:
    explicit DatabaseAccess(QString database_name,QString connnection_name, QString user_name, QString password);
    virtual ~DatabaseAccess() = 0;
    virtual bool ConnectToDatabase() = 0;
    virtual void Disconnect() = 0;
    virtual bool IsConnected() const = 0;

    virtual bool Add(const QString storage,const QList<QString>& keys, const QList<QString> values) = 0;
    virtual bool Del(const QString storage,const QList<QString>& keys) = 0;
    virtual bool Mod(const QString storage, const QList<QString>& keys, const QList<QString> fields, const QList<QString> new_values) = 0;
    virtual bool Ask(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names) = 0;
    virtual QString FetchErrorMSG();
    virtual void ClearCach();
    virtual bool HasNext() const {return _res_cach.size() > 0;}
    virtual QList<QString> FetchNextRow();
    virtual QString GetDatabaseName() const {return _database_name;}
    virtual QString GetUserName() const {return _user_name;}
    virtual QString GetPassword() const {return _password;}
    virtual QString FormView(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names) = 0;
    virtual void StartTransaction()=0;
    virtual void SetARollbackPoint(const QString& point) = 0;
    virtual void Commit() = 0;
    virtual void Rollback(const QString& point) = 0;
    virtual void GetLastInsertIndentification(QString& id)= 0;
protected:
    virtual void SetErrorMSG(QString new_msg){_error_msg = new_msg;}
    void AssignNewRows(QList<QList<QString>>& new_res){_res_cach.swap(new_res);}
    void AppendNewRow(QList<QString> new_row);
private:
    QString _database_name;
    QString _connection_name;
    QString _user_name;
    QString _password;
    QList<QList<QString>> _res_cach;
    QString _error_msg;
signals:
};


#endif // DATABASEACCESS_H

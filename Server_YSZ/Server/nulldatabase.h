#ifndef NULLDATABASE_H
#define NULLDATABASE_H

#include "databaseaccess.h"

class NullDatabase : public DatabaseAccess
{
public:
    NullDatabase();
    ~NullDatabase(){}
    virtual bool ConnectToDatabase();
    virtual void Disconnect(){};
    virtual bool IsConnected() const{return false;} ;
    virtual bool Add(const QString ,const QList<QString>&, const QList<QString> );
    virtual bool Del(const QString ,const QList<QString>& );
    virtual bool Mod(const QString , const QList<QString>& , const QList<QString> , const QList<QString> );
    virtual bool Ask(const QString , const QList<QString>& , const QList<QString> &);
    virtual bool Update(const QMap<QString,QString>&);
    virtual QString FormView(const QString storage, const QList<QString>& constrains, const QList<QString> &field_names);
    virtual void StartTransaction();
    virtual void Commit() ;
    virtual void Rollback(const QString& point) ;
    virtual void SetARollbackPoint(const QString& point);
    virtual void GetLastInsertIndentification(QString& id);
protected:
    void SetErrorMSG(QString new_msg){DatabaseAccess::SetErrorMSG(new_msg);}
private:
    QString _error;
    bool handle();
};

#endif // NULLDATABASE_H

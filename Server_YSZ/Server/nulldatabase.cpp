#include "nulldatabase.h"

NullDatabase::NullDatabase()
    :DatabaseAccess("","","",""),_error("No Available Database!")
{

}

bool NullDatabase::ConnectToDatabase()
{
    return handle();
}

bool NullDatabase::Add(const QString, const QList<QString> &, const QList<QString>)
{
    return handle();
}

bool NullDatabase::Del(const QString, const QList<QString> &)
{
    return handle();
}

bool NullDatabase::Mod(const QString, const QList<QString> &, const QList<QString>, const QList<QString>)
{
    return handle();
}

bool NullDatabase::Ask(const QString, const QList<QString> &, const QList<QString> &)
{
    return handle();
}

bool NullDatabase::Update(const QMap<QString, QString> &)
{
    return handle();
}

QString NullDatabase::FormView(const QString storage, const QList<QString> &constrains, const QList<QString> &field_names)
{
    return "";
}

void NullDatabase::StartTransaction()
{
    handle();
}

void NullDatabase::Commit()
{
    handle();
}

void NullDatabase::Rollback(const QString &point)
{
    handle();
}

void NullDatabase::SetARollbackPoint(const QString &point)
{
    handle();
}

void NullDatabase::GetLastInsertIndentification(QString &id)
{
    handle();
}

bool NullDatabase::handle()
{
    DatabaseAccess::SetErrorMSG(_error);
    return false;
}


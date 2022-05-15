#include "sqldatabase.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
SqlDatabase::SqlDatabase(QString database_name, QString &connection_name, QString user_name, QString password, QString hostname, quint16 port)
    :DatabaseAccess(database_name,connection_name,user_name,password),_hostname(hostname),_port(port)
{
    this->_database = QSqlDatabase::addDatabase("QODBC",connection_name);
}

bool SqlDatabase::ConnectToDatabase()
{
    _database.setHostName(_hostname);
    _database.setPort(_port);
    _database.setDatabaseName(GetDatabaseName());
    _database.setUserName(GetUserName());
    _database.setPassword(GetPassword());

    if(_database.open() == false)
    {
        if(_database.isOpenError())
        {
            QString error = _database.lastError().text();
            SetErrorMSG(error);
        }
        else{
            SetErrorMSG("Open Failed");
        }
        return false;
    }
    else
    {
        return true;
    }
}

void SqlDatabase::Disconnect()
{
    _database.close();
}

bool SqlDatabase::IsConnected() const
{
    return this->_database.isOpen();
}

bool SqlDatabase::Add(const QString storage, const QList<QString> &keys, const QList<QString> values)
{
    QString add_query = "insert into "+storage;
    if(keys.size()!=values.size())
    {
        SetErrorMSG("Add query without equal fields and values");
        return false;
    }
    for(int i=0;i<keys.size();i++)
    {
        if(i == 0)
            add_query += "(";
        add_query += keys[i];
        if(i!=keys.size()-1)
            add_query+=",";
        if(i==keys.size()-1)
            add_query+=") values";
    }
    for(int i=0;i<values.size();i++)
    {
        if(i==0)
            add_query += "(";
        add_query += values[i];
        if(i != values.size() - 1)
            add_query += ",";
        if(i == values.size() - 1)
            add_query += ");";
    }
    return Query(add_query);
}

bool SqlDatabase::Del(const QString storage, const QList<QString> &constrains)
{
    QString del_query = "delete from " + storage + " ";
    del_query += FormWhereClause(constrains);
    del_query += ";";
    return Query(del_query);
}

bool SqlDatabase::Mod(const QString storage, const QList<QString> &constrains, const QList<QString> fields, const QList<QString> new_values)
{
    if(fields.size() != new_values.size())
    {
        SetErrorMSG("Modification without equal number of fields and values");
        return false;
    }
    QString mod_query = "update " + storage +" set ";
    for(int i=0;i<fields.size();i++)
    {
        mod_query += " " + fields[i] + "=" + new_values[i];
        if(i!=fields.size() -1)
            mod_query += ",";
    }
    mod_query += " " + FormWhereClause(constrains) +";";
    return Query(mod_query);
}

bool SqlDatabase::Ask(const QString storage, const QList<QString> &constrains, const QList<QString > &field_names)
{
    QString s = FormView(storage,constrains,field_names);
    s += ";";
    return Query(s);
}

bool SqlDatabase::Query(QString query)
{
    if(IsConnected() == false)
    {
        SetErrorMSG("Database Not Connected");
        return false;
    }
    else{
        QSqlQuery res = QSqlQuery(_database);
        if(res.exec(query))
        {
            ClearCach();
            while(res.next())
            {
                QSqlRecord record = res.record();
                QList<QString> row;
                for(int i=0;i<record.count();i++)
                {
                    row.append(record.value(i).toString());
                    AppendNewRow(row);
                }
            }
            return true;
        }
        else{
            SetErrorMSG(res.lastError().text() + ": executed statement:" + query);
            return false;
        }
    }
}

bool SqlDatabase::Update(const QMap<QString, QString> &map)
{
    if(map.contains("keys") == false)
    {
        SetErrorMSG("Update syntax error: no keys provided");
        return false;
    }
    if(map.contains("key_value") == false)
    {
        SetErrorMSG("Update syntax error: no key_values provided");
        return false;
    }
    if(map.contains("field") == false)
    {
        SetErrorMSG("Update syntax error: no fields provided");
        return false;
    }
    if(map.contains("value") == false)
    {
        SetErrorMSG("Update syntax error: no values provided");
        return false;
    }
    if(map.contains("table") == false)
    {
        SetErrorMSG("Update syntax error: no table provided");
        return false;
    }
    QStringList keys;
    QStringList key_values;
    keys = map["keys"].split(",");//like 'id'
    key_values = map["key_value"].split(",");// like '>3'
    if(keys.size() != key_values.size())
    {
        SetErrorMSG("Update table using Wrong syntax: primary keys'names number is not qeual to values' number{" + map["keys"] + "}:{" + map["key_name"] + "}" );
        return false;
    }
    QString field = map["field"];
    QString value = map["value"];
    QString table = map["table"];
    QString query = "Update "+table +" set " + field +" = " + value+" where ";
    for(int i=0;i<keys.size();i++)
    {
        query += keys[i] + key_values[i];
        if(i != keys.size() - 1)
        {
            query += " and ";
        }
    }
    query += ";";
    return Query(query);
}

QString SqlDatabase::FormView(const QString storage, const QList<QString> &constrains, const QList<QString> &field_names)
{
    QString sel_query = "(select ";
    for(int i=0;i<field_names.size();i++)
    {
        sel_query += field_names[i];
        if(i!=field_names.size()-1)
            sel_query += ",";
    }
    sel_query += " from " + storage + " ";
    QString group_clause = "";
    QString having_caluse = "";
    QString limit_clause = "";
    for(auto it=constrains.begin();it!=constrains.end(); it++)
    {
        if(it->toLower().contains("limit"))
        {
            limit_clause = *it;
        }
        if(it->toLower().contains("group by"))
        {
            group_clause = *it;
        }
        if(it->toLower().contains("having"))
        {
            having_caluse = *it;
        }
    }
    QList<QString> copy = constrains;
    copy.removeOne(group_clause);
    copy.removeOne(having_caluse);
    copy.removeOne(limit_clause);
    sel_query += FormWhereClause(copy) +" ";
    sel_query += group_clause +" ";
    sel_query += having_caluse + " ";
    sel_query += limit_clause +" ";
    sel_query +=")";
    return sel_query;
}

void SqlDatabase::StartTransaction()
{
    Query("start transaction;");
}

void SqlDatabase::Commit()
{
    Query("commit;");
}

void SqlDatabase::Rollback(const QString &point)
{
    Query("rollback to"+point + ";");
}

void SqlDatabase::SetARollbackPoint(const QString &point)
{
    Query("SAVEPOINT "+point + ";");
}

void SqlDatabase::GetLastInsertIndentification(QString &id)
{
    Query("select last_insert_id();");
    if(HasNext())
    {
        id = FetchNextRow()[0];
    }
    else{
        id = "";
    }
}


QString SqlDatabase::FormWhereClause(const QList<QString>& constrains)
{
    if(constrains.size() == 0)
        return "";
    QString clause = " where ";
    for(int i=0;i<constrains.size();i++)
    {
        if(i!=0)
            clause += " and ";
        clause += constrains[i];
    }
    return clause;
}


#include "databaseaccess.h"

DatabaseAccess::DatabaseAccess(QString database_name, QString connnection_name, QString user_name, QString password)
    :_database_name(database_name),_connection_name(connnection_name),_user_name(user_name),_password(password)
{

}

QString DatabaseAccess::FetchErrorMSG()
{
    QString error =this->_error_msg;
    _error_msg = "";
    return error;
}

void DatabaseAccess::ClearCach()
 {
    QList<QList<QString>>ept;
    _res_cach.swap(ept);
}

QList<QString> DatabaseAccess::FetchNextRow()
{
    QList<QString> res;
    if(this->_res_cach.size() == 0)
    {
        return res;
    }
    else{
        res.swap(this->_res_cach[0]);
        _res_cach.pop_front();
        return res;
    }
}

void DatabaseAccess::AppendNewRow(QList<QString> new_row)
{
    this->_res_cach.append(new_row);
}
DatabaseAccess::~DatabaseAccess(){}

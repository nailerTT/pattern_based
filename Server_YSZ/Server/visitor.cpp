#include "visitor.h"
Visitor::Visitor(QObject *parent)
    : QObject{parent}
{

}

QString Visitor::FetchResult()
{
    return this->result;
}

QList<QString> Visitor::get_queries(const QString &query)
{
    QList<QString> res;
    QStringList list = query.split(",");
    QStringListIterator iterator(list);
    while(iterator.hasNext())
        res.append(iterator.next());
    return res;
}

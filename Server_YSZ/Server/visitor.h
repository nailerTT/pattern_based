#ifndef VISITOR_H
#define VISITOR_H

#include <QObject>
class Visitor : public QObject
{
    Q_OBJECT
public:
    explicit Visitor(QObject *parent = nullptr);
    virtual bool QueryLetter(const QString& query) = 0;
    virtual bool QueryStaff(const QString& query) = 0;
    virtual bool QueryCourse(const QString& query) = 0;
    virtual bool QueryActivity(const QString& query) = 0;
    virtual bool QueryDepartment(const QString& query) = 0;
    QString FetchResult();
signals:
protected:
    QList<QString> get_queries(const QString& query);
    void SetResult(QString s){result = s;}
private:
    QString result;
};



#endif // VISITOR_H

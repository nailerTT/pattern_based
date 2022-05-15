#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

#include <QObject>
#include "coursehandler.h"
#include "activityhandler.h"
#include "letterhandler.h"
#include "staffhandler.h"
#include "departmenthandler.h"
enum class HandlerType{
    Course,Activity,Letter,Staff,Department
};

class HandlerFactory : public QObject
{
    Q_OBJECT
public:
    static Handler* GetHandler(HandlerType type);
private:
    explicit HandlerFactory(QObject *parent = nullptr);
    static HandlerFactory Instance;
    CourseHandler ch;
    AcitivityHandler ah;
    Letterhandler lh;
    StaffHandler sh;
    DepartmentHandler dh;
signals:

};


#endif // HANDLERFACTORY_H

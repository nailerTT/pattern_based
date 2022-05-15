#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "lettersystem.h"
#include "activitysystem.h"
#include "coursesystem.h"

class System:public QObject
{
    Q_OBJECT
public:
    explicit System();

private:
    LetterSystem ls;
    ActivitySystem as;
    CourseSystem cs;
};

#endif // SYSTEM_H

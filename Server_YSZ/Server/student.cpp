#include "student.h"

Student::Student(unsigned int id, QString name, Gender gender, RegisterState state)
    : QObject(nullptr),_student_id(id),_name(name),_gender(gender),_state(state)
{

}


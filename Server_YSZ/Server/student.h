#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
enum class Gender {MALE = 0,FEMALE = 1};
enum class RegisterState{FullyRegistered ,PendingRegister,NotRegister};
class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(unsigned int id,QString name,Gender gender,RegisterState state);
    unsigned int GetID () const{return _student_id;}
    Gender GetGender() const {return _gender;}
    bool IsMale() const {return _gender == Gender::MALE;}
    QString GetName()const {return _name;}
    QString SetName(QString new_name){_name = new_name;}
    RegisterState GetState()const {return _state;}
signals:
private:
    const unsigned int _student_id;
    Gender _gender;
    RegisterState _state;
    QString _name;

};

#endif // STUDENT_H

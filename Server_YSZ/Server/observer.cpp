#include "observer.h"
#include "subject.h"
Observer::Observer(Subject *subject)
    : QObject(nullptr),_subject(subject)
{

}
Observer::~Observer()
{
    if(this->_subject)
        this->_subject->RemoveObserer(this);
}

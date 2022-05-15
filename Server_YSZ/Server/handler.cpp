#include "handler.h"

Handler::Handler()
    : QObject{nullptr}
{

}

unsigned int Handler::GetANewId()
{
    return id++;
}
unsigned int Handler::id = 0;

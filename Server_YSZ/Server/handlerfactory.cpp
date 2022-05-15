#include "handlerfactory.h"

Handler *HandlerFactory::GetHandler(HandlerType type)
{
    switch(type)
    {
    case HandlerType::Activity:
        return &(HandlerFactory::Instance.ah);
    case HandlerType::Course:
        return &(HandlerFactory::Instance.ch);
    case HandlerType::Letter:
        return &(HandlerFactory::Instance.lh);
    case HandlerType::Staff:
        return &(HandlerFactory::Instance.sh);
    case HandlerType::Department:
        return &(HandlerFactory::Instance.dh);
    }
}

HandlerFactory::HandlerFactory(QObject *parent)
    : QObject{parent}
{

}
HandlerFactory HandlerFactory::Instance;

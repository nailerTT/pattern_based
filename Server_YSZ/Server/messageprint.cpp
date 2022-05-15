#include "messageprint.h"

MessagePrint::MessagePrint(Subject *subject)
    :Observer(subject)
{

}

bool MessagePrint::Update(const QMap<QString, QString> &map)
{
    PrintMsg(map.begin().value());
}

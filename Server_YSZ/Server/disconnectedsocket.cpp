#include "disconnectedsocket.h"

DisconnectedSocket::DisconnectedSocket()
    : Socket(nullptr,nullptr)
{

}

void DisconnectedSocket::SendOneMessage(QString)
{
    //none
}

void DisconnectedSocket::DisConnect() const
{
    //none
}

QString DisconnectedSocket::Address() const
{
    return "No Host";
}

quint16 DisconnectedSocket::Port() const
{
    return 0;
}

#include "connectedsocket.h"

ConnectedSocket::ConnectedSocket(QTcpSocket *socket)
    : Socket(socket,nullptr)
{
    if(socket == nullptr)
    {
        emit ErrorOccured(this,"A connected socket cannot be nullptr");
    }
}

void ConnectedSocket::SendOneMessage(QString msg)
{
    const QByteArray send_data = msg.toUtf8();
    if(send_data.isEmpty())
        return;
    GetSocket()->write(send_data);
}

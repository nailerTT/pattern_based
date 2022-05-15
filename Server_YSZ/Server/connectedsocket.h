#ifndef CONNECTEDSOCKET_H
#define CONNECTEDSOCKET_H

#include "socket.h"

class ConnectedSocket : public Socket
{
public:
    explicit ConnectedSocket(QTcpSocket* socket);
    void SendOneMessage(QString msg);
};

#endif // CONNECTEDSOCKET_H

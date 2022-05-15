#ifndef DISCONNECTEDSOCKET_H
#define DISCONNECTEDSOCKET_H

#include "socket.h"
#include <QDebug>
class DisconnectedSocket : public Socket
{
public:
    explicit DisconnectedSocket();
    virtual void SendOneMessage(QString msg);
    virtual void DisConnect() const;
    virtual QString Address() const;
    virtual quint16 Port() const;
protected slots:
    virtual void EmitReadReady(){}
    virtual void EmitErrorOccured(){}
    virtual void EmitDisconnected(){}

};

#endif // DISCONNECTEDSOCKET_H

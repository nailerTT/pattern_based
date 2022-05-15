#ifndef SOCKET_H
#define SOCKET_H

#include "QVector"
#include "QTcpSocket"
class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QTcpSocket* socket,QObject *parent = nullptr);
    virtual ~Socket(){
        if(_socket!=nullptr)
            _socket->abort();
        delete _socket;
        _socket = nullptr;
    }
    virtual void SendOneMessage(QString msg) = 0;
    virtual void DisConnect() const;
    virtual QString Address() const;
    virtual quint16 Port() const;
    QVector<QString> PopAllMSG() ;

signals:
    void ReadReady(Socket*);
    void NewMessage(Socket*,QString msg);
    void MessageQueueEmpty(Socket*);
    void ErrorOccured(Socket*,QString error);
    void Disconnected(Socket*);
protected slots:
    virtual void EmitReadReady();
    virtual void EmitErrorOccured();
    virtual void EmitDisconnected();

protected:
    QTcpSocket* GetSocket(){return this->_socket;}
private:
    QTcpSocket* _socket;
    QVector<QString> _msgs;
};

#endif // SOCKET_H

#include "socket.h"
#include <QDebug>
Socket::Socket(QTcpSocket* socket,QObject *parent)
    : QObject{parent},_socket(socket)
{
    if(socket!=nullptr)
    {
        connect(socket,&QTcpSocket::readyRead,this,&Socket::EmitReadReady);
        connect(socket,&QTcpSocket::errorOccurred,this,&Socket::EmitErrorOccured);
        connect(socket,&QTcpSocket::disconnected,this,&Socket::EmitDisconnected);
    }
}

void Socket::DisConnect() const
{
    this->_socket->disconnectFromHost();
    if(this->_socket->state()!=QAbstractSocket::UnconnectedState)
    {
        this->_socket->abort();
    }
    this->_socket->setParent(nullptr);
}

QString Socket::Address() const
{
    return _socket?_socket->peerAddress().toString():"None";
}

quint16 Socket::Port() const
{
    return _socket?_socket->peerPort():0;
}

QVector<QString> Socket::PopAllMSG()
{
    QVector<QString> ret;
    ret.swap(this->_msgs);
    emit MessageQueueEmpty(this);
    return ret;
}

void Socket::EmitReadReady()
{
    if(this->_socket->bytesAvailable()<=0)
    {
        return;
    }
    else
    {
        const QString recv_text ="{"+ QString::fromUtf8(this->_socket->readAll())+"}";
        //this->_socket->write(QString("{hello world}").toUtf8());
        bool over = true;
        unsigned int start;
        for(int i = 0; i < recv_text.size();i++)
        {
            if(recv_text[i]=='{')
            {
                if(over)
                {
                    over = false;
                    start = i;
                }
            }
            else if(recv_text[i] == '}')
            {
                if(!over)
                {
                    over = true;
                    QString one = recv_text.mid(start + 1,i-start-1);
                    this->_msgs.push_back(one);
                    emit NewMessage(this,one);
                }
            }
        }
        emit ReadReady(this);
    }
}


void Socket::EmitErrorOccured()
{
    QString error = QString("[%1:%2] Socket Error:%3").arg(this->_socket->peerAddress().toString())
                  .arg(this->_socket->peerPort()).arg(this->_socket->errorString());
    emit this->ErrorOccured(this,error);
}

void Socket::EmitDisconnected()
{
    emit Disconnected(this);
}


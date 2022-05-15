#ifndef NETWORKLISENER_H
#define NETWORKLISENER_H
#include <QQueue>
#include <QList>
#include <QTcpServer>
#include "socket.h"
#include <QHostAddress>
#include "consolemessageshow.h"
#include "disconnectedsocket.h"
#include "QPair"
#include "subject.h"
#include "observer.h"
class NetWorkLisener:public Subject
{
    Q_OBJECT
public:
    NetWorkLisener(int max_clients,Observer* printer  = new ConsoleMessageShow());
    void InitServer(const QString address = "Any", const unsigned short port = 6666);
    void CloseServer();
    ~NetWorkLisener();
    bool HasNext();
    QString Next();
    QString CurrentClients();
private:
    QList<QPair<int,QList<QString>>> _received_msg;
    QVector<int> _clients;
    QTcpServer* _server;
    void RemoveSocket(unsigned int i);
    void RemoveSocket(const Socket*socket);
    int AssignSocket(Socket* socket);
    Socket *FetchSockst(unsigned int idx);
    QList<QPair<Socket*,bool>> _sockets_pool;
    DisconnectedSocket*_vacant_socket;
    void DisconnectSocketAt(unsigned int idx);
signals:
    void NewMsg(QString msg);
private slots:
    void NewClients();
    void SocketReadReady(Socket*);
    void ClientDisconnected(const Socket*);
    void SocketErrorOccured(const Socket*socket, QString error);
    void ServerErrorOccured(QAbstractSocket::SocketError);
    void ReceiveNewMSG(const Socket*socket,QString msg);
};

#endif // NETWORKLISENER_H

#include "networklisener.h"
#include "connectedsocket.h"
#include "disconnectedsocket.h"

NetWorkLisener::NetWorkLisener(int max_clients, Observer* printer)
    :_server(nullptr),_vacant_socket(new DisconnectedSocket)
{
    if(printer != nullptr)
        AddObserver(printer);
    this->_sockets_pool.resize(max_clients,{nullptr,true});
}

void NetWorkLisener::InitServer(const QString address, const unsigned short port )
{
    CloseServer();
    this->_server = new QTcpServer();
    const QHostAddress _address = (address == "Any")?QHostAddress::Any :QHostAddress(address);
    const unsigned short _port = port;
    if(_server->listen(_address,_port) == false)
    {
        this->_server->close();
        delete this->_server;
        this->_server = nullptr;
        //_printer->PrintError("server socket init fails");
        QMap<QString,QString> map;
        map.insert("msg","server socket init fails");
        NotiFy(map);
    }
    else{
        connect(_server,&QTcpServer::newConnection,this,&NetWorkLisener::NewClients);
    }
}

//socket* pointers are tackled well
void NetWorkLisener::CloseServer()
{
    if(_server!=nullptr){
        _server->close();
        for(int i=0;i<this->_sockets_pool.size();i++)
        {
            this->DisconnectSocketAt(i);
        }
        QVector<int> empty;
        this->_clients.swap(empty);
        delete _server;
        _server = nullptr;
        QQueue<QPair<int,QList<QString>>> ept;
        this->_received_msg.swap(ept);
    }
}
//using CloseServer to delete socket pointers
NetWorkLisener::~NetWorkLisener()
{
    this->CloseServer();
    delete this->_vacant_socket;
    for(int i=0;i<this->_sockets_pool.size();i++)
    {
        if(!this->_sockets_pool[i].second)
        {
            this->_sockets_pool[i].first->DisConnect();
            delete this->_sockets_pool[i].first;
        }
    }
}
//not deletion of socket pointers
bool NetWorkLisener::HasNext()
{
    return _received_msg.size() > 0;
}

//not deletion of socket pointers
QString NetWorkLisener::Next()
{
    QPair<int,QList<QString>> p = this->_received_msg.front();
    QString msg = p.second.front();
    p.second.pop_front();
    return msg;
}

QString NetWorkLisener::CurrentClients()
{
    QString res;
    for(auto& p:_received_msg)
    {
        res += QString("[Add:%1,Port:%2]:\n").arg(FetchSockst(p.first)->Address()).arg(FetchSockst(p.first)->Port());
        for(auto& s:p.second)
            res+="\t"+ s + "\n";
    }
    return res;
}

void NetWorkLisener::RemoveSocket(unsigned int i)
{
    if(i >= this->_sockets_pool.size())
        return;
    for(auto it = this->_received_msg.begin();it!=_received_msg.end();it ++)
    {
        if(it->first == i)
        {
            this->_received_msg.erase(it);
            break;
        }
    }
    this->_clients.removeOne(i);
    this->_sockets_pool[i].second = true;
}

void NetWorkLisener::RemoveSocket(const Socket *socket)
{
    int idx = -1;
    for(int i=0;i<this->_sockets_pool.size();i++)
    {
        if(this->_sockets_pool[i].first == socket)
        {
            idx = i;
        }
    }
    if(idx>=0)
    {
        RemoveSocket(idx);
    }
}

int NetWorkLisener::AssignSocket(Socket *socket)
{
    int res = -1;
    for(int i=0;i<this->_sockets_pool.size();i++)
    {
        if(this->_sockets_pool[i].second)
        {
            if(this->_sockets_pool[i].first!=this->_vacant_socket)
            {
                Socket* s = this->_sockets_pool[i].first;

                delete s;
                this->_sockets_pool[i].first = nullptr;
            }
            this->_sockets_pool[i].first = socket;
            this->_sockets_pool[i].second = false;
            res = i;
            break;
        }
    }
    return res;
}

Socket *NetWorkLisener::FetchSockst(unsigned int idx)
{
    if(idx >= this->_sockets_pool.size())
    {
        return this->_vacant_socket;
    }
    else{
        if(this->_sockets_pool[idx].second)
        {
            return this->_vacant_socket;
        }
        else
            return this->_sockets_pool[idx].first;
    }
}

void NetWorkLisener::DisconnectSocketAt(unsigned int idx)
{
    if(idx >= this->_sockets_pool.size())
        return;
    FetchSockst(idx)->DisConnect();
    RemoveSocket(idx);
}

void NetWorkLisener::NewClients()
{
    while(_server->hasPendingConnections())
    {
        Socket* socket = new ConnectedSocket(_server->nextPendingConnection());
        int idx = AssignSocket(socket);
        //failes
        if(idx == -1)
        {
            delete socket;
            return;
        }
        _clients.push_back(idx);
        QMap<QString,QString> map;
        map.insert("msg",QString("client from [%1,%2] successfully connect").arg(FetchSockst(idx)->Address()).arg(FetchSockst(idx)->Port()));
        NotiFy(map);
        connect(FetchSockst(idx),&Socket::NewMessage,this,&NetWorkLisener::ReceiveNewMSG);
        // when read is ready
        connect(FetchSockst(idx),&Socket::ReadReady,this,&NetWorkLisener::SocketReadReady);
        //when something wrong happens
        connect(FetchSockst(idx),&Socket::ErrorOccured,this,&NetWorkLisener::SocketErrorOccured);
        //disconnect
        connect(FetchSockst(idx),&Socket::Disconnected,this,&NetWorkLisener::ClientDisconnected);
    }
    connect(_server,&QTcpServer::acceptError,this,&NetWorkLisener::ServerErrorOccured);
}



void NetWorkLisener::SocketReadReady(Socket *socket)
{
    QList<QString> msgs = socket->PopAllMSG();
    bool has = false;
    int idx = -1;
    for(auto it = this->_received_msg.begin();it!=this->_received_msg.end();it++)
    {
        idx = it->first;
        if(this->_sockets_pool[idx].first == socket)
        {
            it->second.append(msgs);
            has = true;
            break;
        }
    }
    if(idx > 0 && !has)
    {
        _received_msg.append({idx,msgs});
    }
}

void NetWorkLisener::ClientDisconnected(const Socket *socket)
{
    QString add = socket->Address();
    quint16 port = socket->Port();
    RemoveSocket(socket);
    QMap<QString,QString> map;
    map.insert("msg",QString("[%1,%2] Socket disconnected").arg(add).arg(port));
    NotiFy(map);
}

void NetWorkLisener::SocketErrorOccured(const Socket *socket, QString error)
{
    socket->DisConnect();
    RemoveSocket(socket);
    QMap<QString,QString> map;
    map.insert("msg",error);
    NotiFy(map);
}

void NetWorkLisener::ServerErrorOccured(QAbstractSocket::SocketError)
{
    QMap<QString,QString> map;
    map.insert("msg","Server Error:" + _server->errorString());
    NotiFy(map);
    CloseServer();
}

void NetWorkLisener::ReceiveNewMSG(const Socket *socket, QString msg)
{
    QMap<QString,QString> map;
    map.insert("msg",QString("\n[%1,%2] sent:"+msg+"\n").arg(socket->Address()).arg(socket->Port()));
    NotiFy(map);
    emit NewMsg(msg);
}


#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "abstractsocket.hpp"

namespace netutils
{


class TcpSocket : public AbstractSocket
{

public:
    TcpSocket(NetworkAddress::Family family);
    ~TcpSocket() override;

    int listen(int backlog);

	int accept(TcpSocket &socket, NetworkAddress &address);

};


}

#endif // TCPSOCKET_H

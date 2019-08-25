#include "tcpsocket.hpp"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace netutils
{


TcpSocket::TcpSocket(NetworkAddress::Family family)
{
	int af;
	if (family == NetworkAddress::IPv4)
		af = AF_INET;
	else if (family == NetworkAddress::IPv6)
		af = AF_INET6;
	else
		return;

	_handle = ::socket(af, SOCK_STREAM, 0);
	_family = family;
}

TcpSocket::~TcpSocket()
{
	::shutdown(_handle, SHUT_RD);
	::shutdown(_handle, SHUT_WR);
}

int TcpSocket::listen(int backlog)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	return ::listen(_handle, backlog);
}

int TcpSocket::accept(TcpSocket &socket, NetworkAddress &address)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	sockaddr_storage sa;
	socklen_t socklen = sizeof(sa);

	int fd = ::accept(_handle, (sockaddr *) &sa, &socklen);
	if (fd == -1)
	{
		return -1;
	}

	// TODO: fill address
	socket.setDescriptor(fd);

	return 0;
}


}
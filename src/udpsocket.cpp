#include "udpsocket.hpp"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace netutils
{


UdpSocket::UdpSocket(NetworkAddress::Family family)
{
	int af;
	if (family == NetworkAddress::IPv4)
		af = AF_INET;
	else if (family == NetworkAddress::IPv6)
		af = AF_INET6;
	else
		return;

	_handle = ::socket(af, SOCK_DGRAM, 0);
	_family = family;
}

int UdpSocket::sendTo(const void *data, size_t &len, const NetworkAddress &address)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	ssize_t ret = ::sendto(_handle, data, len, 0, (sockaddr *) address.sa(), sizeof(*address.sa()));
	if (ret == -1)
	{
		return -1;
	}

	len = static_cast<size_t>(ret);
	return 0;
}

int UdpSocket::recvFrom(void *data, size_t &len, NetworkAddress &address)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	sockaddr_storage sa;
	socklen_t socklen = sizeof(sa);

	ssize_t ret = ::recvfrom(_handle, data, len, 0, (sockaddr *) &sa, &socklen);
	if (ret == -1)
	{
		return -1;
	}

	address = NetworkAddress((sockaddr *) &sa);
	len = static_cast<size_t>(ret);
	return 0;
}


}
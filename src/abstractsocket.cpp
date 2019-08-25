#include "abstractsocket.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>

// TODO:
// Write setsockopt

namespace netutils
{


AbstractSocket::~AbstractSocket()
{ close(); }

int AbstractSocket::handle() const
{
	return _handle;
}

int AbstractSocket::setDescriptor(int fd)
{
	if (_handle != -1)
	{
		close();
	}

	sockaddr_storage sa;
	socklen_t socklen = sizeof(sa);

	int ret = getsockname(fd, (sockaddr *) &sa, &socklen);
	if (ret == -1)
	{
		return -1;
	}

	NetworkAddress address((sockaddr *) &sa);
	_handle = fd;
	_family = address.family();

	return 0;
}

int AbstractSocket::bind(const NetworkAddress &address)
{
	if (_handle == -1 || !address.valid())
	{
		errno = EINVAL;
		return -1;
	}

	int ret = ::bind(_handle, (sockaddr *) address.sa(), sizeof(sockaddr_un));
	if (ret == -1)
	{
		return -1;
	}

	return 0;
}

int AbstractSocket::connect(const NetworkAddress &address)
{
	if (_handle == -1 || !address.valid())
	{
		errno = EINVAL;
		return -1;
	}

	int ret = ::connect(_handle, (sockaddr *) address.sa(), sizeof(sockaddr_un));
	if (ret == -1)
	{
		return -1;
	}

	return 0;
}

int AbstractSocket::send(const void *data, size_t &len)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	ssize_t ret = ::send(_handle, data, len, 0);
	if (ret == -1)
	{
		return -1;
	}

	len = static_cast<size_t>(ret);
	return 0;
}

int AbstractSocket::recv(void *data, size_t &len)
{
	if (_handle == -1)
	{
		errno = EINVAL;
		return -1;
	}

	ssize_t ret = ::recv(_handle, data, len, 0);
	if (ret == -1)
	{
		return -1;
	}

	len = static_cast<size_t>(ret);
	return 0;
}

int AbstractSocket::setNonBlocking(bool blocking)
{
	int ret, oldfl;

	oldfl = fcntl(_handle, F_GETFL);
	if (oldfl == -1)
	{
		return -1;
	}

	ret = ::fcntl(_handle, F_SETFL, (blocking) ? oldfl | O_NONBLOCK : oldfl & ~O_NONBLOCK);
	if (ret == -1)
	{
		return -1;
	}

	return 0;
}

int AbstractSocket::setSocketOption(SocketOption option, int value)
{
	int ret;

	if (option == BroadcastOption)
	{
		ret = ::setsockopt(_handle, SOL_SOCKET, SO_BROADCAST, &value, sizeof(value));
		if (ret == -1)
		{
			return -1;
		}
	}
	else
	{
		errno = EINVAL;
		return -1;
	}

	return 0;
}

void AbstractSocket::close()
{
	::close(_handle);
	_handle = -1;
}


}
#include "networkaddress.hpp"

#include <cstring>
#include <arpa/inet.h>
#include <sys/un.h>

/*
 * TODO:
 * Create constants for loopback/broadcast addresses
 * Get NetworkAddress by DNS name
*/

namespace netutils
{


NetworkAddress::NetworkAddress()
{
}

NetworkAddress::NetworkAddress(Family family, std::string address, uint16_t port)
{
	int ret;

	::memset(_sockaddr.get(), 0, sizeof(sockaddr_storage));

	if (family == IPv4 || family == Unspec)
	{
		auto *in4 = reinterpret_cast<sockaddr_in *>(_sockaddr.get());
		ret = inet_pton(AF_INET, address.c_str(), &in4->sin_addr);
		if (ret == 1)
		{
			in4->sin_family = AF_INET;
			in4->sin_port = ntohs(port);

			_family = IPv4;
			_address = address;
			_port = port;
			return;
		}
	}

	if (family == IPv6 || family == Unspec)
	{
		auto *in6 = reinterpret_cast<sockaddr_in6 *>(_sockaddr.get());
		ret = inet_pton(AF_INET6, address.c_str(), &in6->sin6_addr);
		if (ret == 1)
		{
			in6->sin6_family = AF_INET6;
			in6->sin6_port = ntohs(port);

			_family = IPv6;
			_address = address;
			_port = port;
			return;
		}
	}

	if (family == Unix)
	{
		auto *un = reinterpret_cast<sockaddr_un *>(_sockaddr.get());
		if (address.size() < sizeof(un->sun_path))
		{
			un->sun_family = AF_UNIX;
			::strncpy(un->sun_path, address.c_str(), address.size());
			_family = Unix;
			_address = address;
		}
	}
}

NetworkAddress::NetworkAddress(const sockaddr *sa)
{
	char address[255];

	if (sa->sa_family == AF_INET)
	{
		const auto *in = reinterpret_cast<const sockaddr_in *>(sa);
		if (inet_ntop(in->sin_family, &in->sin_addr, address, sizeof(address)) != nullptr)
		{
			memcpy(_sockaddr.get(), in, sizeof(*in));

			_family = Family::IPv4;
			_address = address;
		}
	}

	if (sa->sa_family == AF_INET6)
	{
		const auto *in6 = reinterpret_cast<const sockaddr_in6 *>(sa);
		if (inet_ntop(in6->sin6_family, &in6->sin6_addr, address, sizeof(address)) != nullptr)
		{
			memcpy(_sockaddr.get(), in6, sizeof(*in6));

			_family = Family::IPv6;
			_address = address;
		}
	}

	if (sa->sa_family == AF_UNIX)
	{
		const auto *un = reinterpret_cast<const sockaddr_un *>(sa);

		memcpy(_sockaddr.get(), un, sizeof(*un));

		strncpy(address, un->sun_path, sizeof(un->sun_path));

		_family = Family::Unix;
		_address = address;
	}
}

bool NetworkAddress::valid() const
{
	return !_address.empty();
}

NetworkAddress::Family NetworkAddress::family() const
{
	return _family;
}

std::string NetworkAddress::address() const
{
	return _address;
}

const sockaddr_storage *NetworkAddress::sa() const
{
	return _sockaddr.get();
}


}
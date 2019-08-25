#ifndef NETWORKADDRESS_H
#define NETWORKADDRESS_H

#include <string>
#include <memory>

#include <sys/socket.h>

namespace netutils
{


class NetworkAddress
{

public:
	enum Family
	{
		Unknown = 0,
		Unspec,
		IPv4,
		IPv6,
		Unix
	};

	enum
	{
		AnyPort = 0
	};

public:
	/*!
	 * @brief Make empty network address for further use.
	 * For example, TODO.
	 */
	NetworkAddress();

	/*!
	 * @brief Make network address from string.
	 * For example, NetworkAddress(NetworkAddress::IPv4, "0.0.0.0", 8888).
	 * @param family
	 * @param address
	 * @param port
	 */
	NetworkAddress(Family family, std::string address, uint16_t port = AnyPort);

	/*!
	 * @brief Make network address from existing struct sockaddr.
	 * @param sa - sockaddr struct.
	 */
	NetworkAddress(const struct sockaddr *sa);

	/*!
	 * @brief Check valid address or not.
	 * @return true - address is valid, false - vice versa
	 */
	bool valid() const;

	/*!
	 * @brief Network address family.
	 * @return family.
	 */
	Family family() const;

	/*!
	 * @brief String representation of the network address.
	 * @return string.
	 */
	std::string address() const;

	/*!
	 * @brief struct sockaddr_storage.
	 * @return struct.
	 */
	const sockaddr_storage *sa() const;

private:
	Family _family = Unknown;
	std::string _address = "";
	unsigned int _port = 0;
	std::shared_ptr<sockaddr_storage> _sockaddr = std::make_shared<sockaddr_storage>();

};


}

#endif // NETWORKADDRESS_H

#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H

#include <string>

#include "networkaddress.hpp"

namespace netutils
{


class AbstractSocket
{

public:
	enum Type
	{
		Stream = 0,
		Datagram,
		Seqpacket,
		Raw,
		Undefined
	};

	enum SocketOption
	{
		BroadcastOption,
		ReuseAddressOption
	};

public:
	virtual ~AbstractSocket() = 0;

	/*!
	 * @brief Return file descriptor.
	 * @return fd
	 */
	int handle() const;

	 /*!
	  * @brief Set file descriptor.
	  * @param fd
	  * @return 0 on success, otherwise -1 with errno value.
	  */
	int setDescriptor(int fd);

	/*!
	 * @brief Bind socket.
	 * @param address
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int bind(const NetworkAddress &address);

	/*!
	 * @brief Connect socket.
	 * @param address
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int connect(const NetworkAddress &address);

	/*!
	 * @brief Send data.
	 * @param data
	 * @param len
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int send(const void *data, size_t &len);

	/*!
	 * @brief Receive data.
	 * @param data
	 * @param len
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int recv(void *data, size_t &len);

	/*!
	 * Enable or disable non-blocking mode.
	 * @param blocking
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int setNonBlocking(bool blocking);

	/*!
	 * Set socket option.
	 * @param option
	 * @param value
	 * @return 0 on success, otherwise -1 with errno value.
	 */
	int setSocketOption(SocketOption option, int value);

	/*!
	 * @brief Close fd.
	 */
	void close();

protected:
	int _handle = -1;
	NetworkAddress::Family _family = NetworkAddress::Unknown;

};


}

#endif // ABSTRACTSOCKET_H

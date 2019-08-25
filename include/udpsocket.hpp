#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "abstractsocket.hpp"

#include <string>

namespace netutils
{


class UdpSocket : public AbstractSocket
{

public:
	/*!
	 *
	 * @param family
	 */
	UdpSocket(NetworkAddress::Family family);

	~UdpSocket() override = default;

	/*!
	 *
	 * @param buf
	 * @param len
	 * @param address
	 * @return
	 */
    int sendTo(const void *buf, size_t &len, const NetworkAddress &address);

    /*!
     *
     * @param buf
     * @param len
     * @param address
     * @return
     */
	int recvFrom(void *buf, size_t &len, NetworkAddress &address);

};


}

#endif // UDPSOCKET_H

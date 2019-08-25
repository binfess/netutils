#include <iostream>
#include <array>
#include <cstring>

#include <udpsocket.hpp>

int main()
{
	using namespace netutils;

	UdpSocket sock(NetworkAddress::Family::IPv4);

    // sock.setNonBlocking(true);
    // sock.setSocketOption(UdpSocket::BroadcastOption, 1);

	if (sock.bind(NetworkAddress(NetworkAddress::IPv4, "0.0.0.0", 45000)))
	{
		std::cerr << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}

	std::array<std::uint8_t, 65537> buffer{0};
	while (1)
	{
		size_t len = buffer.size();

		NetworkAddress peer;
		if (sock.recvFrom(buffer.data(), len, peer))
		{
			std::cerr << strerror(errno) << std::endl;
		}

		std::cout << peer.address() << std::endl;
		std::cout << len << ": " << buffer.size() << std::endl;
	}
	
	return 0;
}

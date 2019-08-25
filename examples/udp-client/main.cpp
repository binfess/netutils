#include <iostream>
#include <array>
#include <cstring>

#include <udpsocket.hpp>

int main()
{
	using namespace netutils;

	auto server_address = NetworkAddress(NetworkAddress::IPv4, "127.0.0.1", 45000);

	UdpSocket sock(NetworkAddress::IPv4);

	std::array<std::uint8_t, 65507> buffer{0};

	size_t len = buffer.size();
	if (sock.sendTo(buffer.data(), len, server_address))
	{
		std::cerr << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}

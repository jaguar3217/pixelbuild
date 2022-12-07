#include <iostream>
#include <SFML/Network.hpp>
#include "Client.hpp"
#include "states.hpp"

#include <Windows.h>

int main()
{
	sf::UdpSocket socket;
	std::vector<Client> clients;
	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	char level[128];

	if (socket.bind(25635) != sf::Socket::Done)
	{
		std::cerr << "[pbserverd] cannot bind to port 25635 (UDP)\n";
		return 1;
	}

	while (true)
	{
		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{
			std::cerr << "[pbserverd] connection lost from " << sender << '\n';
		}
		sf::Int8 cmd;
		packet >> cmd;
		switch (cmd)
		{
		case 0: {
			while (true)
			{
				sf::Packet spacket;
				sf::IpAddress rip = sf::IpAddress(rand(), rand(), rand(), rand());
				unsigned short rport = rand();
				spacket << (sf::Int8)0 << rip.toInteger() << rport;
				if (socket.send(spacket, sender, port) != sf::Socket::Done)
					std::cerr << "[pbserverd] Cannot send Client Connected packet to " << sender << ':' << port << '\n';
				// Send Move X/Y
				spacket.clear();
				spacket << (sf::Int8)2 << rip.toInteger() << rport << rand() % 512 << rand() % 256; // Move X/Y
				if (socket.send(spacket, sender, port) != sf::Socket::Done)
					std::cerr << "[pbserverd] cannot send X/Y data to " << sender << ':' << port << '\n';
				std::cout << "[pbserverd] New client added: " << rip << " with port " << port << ".\n";
				Sleep(1000);
			}
			break;
		}
		}
	}
	return 0;
}
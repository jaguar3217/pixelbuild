#include <iostream>
#include <SFML/Network.hpp>
#include "Globals.hpp"
#include "Client.hpp"
#include "states.hpp"
#include "Functions.hpp"

int main()
{
	sf::FileInputStream levelFile;
	if (levelFile.open("main.pblvl"))
		levelFile.read(level, 128);

	if (socket.bind(25635) != sf::Socket::Done)
	{
		std::cerr << "[pbserverd] cannot bind to port 25635 (UDP)\n";
		return 1;
	}

	socket.setBlocking(false);

	mainLoop: while (true)
	{
		socket.receive(packet, sender, port);
		if (sender.toInteger() == 0) goto mainLoop;

		sf::Int8 cmd;
		packet >> cmd;
		switch (cmd)
		{
		case 0: { // Indicate Connection
			addClient(sender, port);
			break;
		}
		case 1: { // Indicate Disconnection
			removeClient(sender, port);
			break;
		}
		case 2: { // Move X/Y
			int x, y;
			packet >> x >> y;
			setPosition(sender, port, x, y);
			break;
		}
		case 3: { // Set Animation Frame
			int frame;
			packet >> frame;
			setAnimFrame(sender, port, frame);
			break;
		}
		case 4: { // Set State
			int state;
			packet >> state;
			setState(sender, port, state);
			break;
		}
		case 5: { // Recv Chat
			sf::String msg;
			packet >> msg;
			sf::Packet s_packet;
			s_packet << (sf::Int8)6 << sender.toInteger() << port << msg;
			broadcastAll(s_packet);
		}
		}
	}
	return 0;
}
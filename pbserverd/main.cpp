#include <iostream>
#include <SFML/Network.hpp>
#include "Globals.hpp"
#include "Client.hpp"
#include "states.hpp"
#include "Functions.hpp"

int main(int argc, char** argv)
{
	if (argc < 2) return 1;

	sf::FileInputStream levelFile;
	char wh[2];
	if (levelFile.open(argv[1]))
	{
		levelFile.read(wh, 2);
		level = new char[wh[0] * wh[1]];
		levelFile.read(level, wh[0] * wh[1]);
		levelWidth = wh[0];
		levelHeight = wh[1];
	}

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
		}
	}
	return 0;
}
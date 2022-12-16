#include "Functions.hpp"
#include "Client.hpp"
#include "Globals.hpp"

#include <iostream>

void addClient(sf::IpAddress sender, unsigned short port)
{
	Client c;
	c.ip = sender;
	c.port = port;
	c.x = 0;
	c.y = 0;
	clients.push_back(c);
}

void removeClient(sf::IpAddress sender, unsigned short port)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients.erase(clients.begin() + position);
	}
}

void setPosition(sf::IpAddress sender, unsigned short port, int x, int y)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].x = x;
		clients[position].y = y;
	}
}

void setAnimFrame(sf::IpAddress sender, unsigned short port, int frame)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].frame = frame;
	}
}

void setState(sf::IpAddress sender, unsigned short port, int state)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].state = state;
	}
}

//---//

int findElement(sf::IpAddress sender, unsigned short port)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].ip == sender && clients[i].port == port)
			return i;
	}
	return -1;
}
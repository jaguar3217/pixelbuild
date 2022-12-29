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

	sf::Packet packet;
	packet << (sf::Int8)0 /* Client Connected */ << sender.toInteger() << port;
	broadcast(sender, port, packet);

	for (Client& c : clients)
		if (!(c.ip == sender && c.port == port))
		{
			sf::Packet packet;
			packet << (sf::Int8)0 /* Client Connected */ << c.ip.toInteger() << c.port;
			socket.send(packet, sender, port);
			packet.clear();
			packet << (sf::Int8)2 /* Move X/Y */ << c.ip.toInteger() << c.port << c.x << c.y;
			socket.send(packet, sender, port);
			packet.clear();
			packet << (sf::Int8)3 /* Send Frame */ << c.ip.toInteger() << c.port << c.frame;
			socket.send(packet, sender, port);
			packet.clear();
			packet << (sf::Int8)4 /* Send State */ << c.ip.toInteger() << c.port << c.state;
			socket.send(packet, sender, port);
		}
}

void removeClient(sf::IpAddress sender, unsigned short port)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients.erase(clients.begin() + position);
	}

	sf::Packet packet;
	packet << (sf::Int8)1 /* Client Disconnected */ << sender.toInteger() << port;
	broadcast(sender, port, packet);
}

void setPosition(sf::IpAddress sender, unsigned short port, int x, int y)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].x = x;
		clients[position].y = y;
	}

	sf::Packet packet;
	packet << (sf::Int8)2 /* Move X/Y */ << sender.toInteger() << port << x << y;
	broadcast(sender, port, packet);
}

void setAnimFrame(sf::IpAddress sender, unsigned short port, int frame)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].frame = frame;
	}

	sf::Packet packet;
	packet << (sf::Int8)3 /* Set Animation Frame */ << sender.toInteger() << port << frame;
	broadcast(sender, port, packet);
}

void setState(sf::IpAddress sender, unsigned short port, int state)
{
	int position = findElement(sender, port);
	if (position != -1)
	{
		clients[position].state = state;
	}

	sf::Packet packet;
	packet << (sf::Int8)4 /* Set State */ << sender.toInteger() << port << state;
	broadcast(sender, port, packet);
}

void broadcast(sf::IpAddress sender, unsigned short port, sf::Packet packet)
{
	for (Client & c : clients)
		if (!(c.ip == sender && c.port == port))
			socket.send(packet, c.ip, c.port);
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
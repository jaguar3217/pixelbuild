#pragma once

#include <SFML/Network.hpp>
#include "Client.hpp"

extern sf::UdpSocket socket;
extern std::vector<Client> clients;
extern sf::Packet packet;
extern sf::IpAddress sender;
extern unsigned short port;
extern char level[128];
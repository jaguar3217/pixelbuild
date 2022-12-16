#pragma once

#include <SFML/Network.hpp>
#include "Client.hpp"

void addClient(sf::IpAddress sender, unsigned short port);
void removeClient(sf::IpAddress sender, unsigned short port);
void setPosition(sf::IpAddress sender, unsigned short port, int x, int y);
void setAnimFrame(sf::IpAddress sender, unsigned short port, int frame);
void setState(sf::IpAddress sender, unsigned short port, int state);

int findElement(sf::IpAddress sender, unsigned short port);
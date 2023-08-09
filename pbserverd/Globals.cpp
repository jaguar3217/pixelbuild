#include "Globals.hpp"

sf::UdpSocket socket;
std::vector<Client> clients;
sf::Packet packet;
sf::IpAddress sender;
unsigned short port;
char* level;
int levelWidth, levelHeight;
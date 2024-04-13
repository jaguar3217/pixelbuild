#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include "Client.hpp"

class Server {
public:
    Server();
    ~Server();
    bool loadLevel(const std::string& filePath);
    void run();

private:
    sf::UdpSocket socket;
    std::vector<Client> clients;
    std::unique_ptr<char[]> level;
    int levelWidth, levelHeight;

    void addClient(sf::IpAddress sender, unsigned short port);
    void sendTilemap(sf::IpAddress recipient, unsigned short port);
    void removeClient(sf::IpAddress sender, unsigned short port);
    void setPosition(sf::IpAddress sender, unsigned short port, int x, int y);
    void setAnimFrame(sf::IpAddress sender, unsigned short port, int frame);
    void setState(sf::IpAddress sender, unsigned short port, int state);
    void broadcast(sf::IpAddress sender, unsigned short port, sf::Packet& packet);
    int findElement(sf::IpAddress sender, unsigned short port);
};

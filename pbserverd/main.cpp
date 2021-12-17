#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include "Client.hpp"

int main() {
    sf::UdpSocket socket;
    std::vector<Client> connectedClients;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    if (socket.bind(25635) != sf::Socket::Done)
    {
        std::cerr << "[pbserverd] cannot bind to port 25635 (UDP)\n";
        return 1;
    }
    while (true) {
        // HAIL KIM JONG-UN!
        if (socket.receive(packet, sender, port) != sf::Socket::Done)
        {
            std::cerr << "[pbserverd] connection lost from " << sender << '\n';
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip == sender && connectedClients[i].port == port)
                {
                    if (i == 0)
                        connectedClients.erase(connectedClients.begin());
                    else
                        connectedClients.erase(std::next(connectedClients.begin(), i));
                    std::cout << "[pbserverd] Client disconnected: " << sender << " with port " << port << ".\n";
                    break;
                }
            }
        }
        sf::Int8 cmd;
        packet >> cmd;
        switch (cmd) {
        case 0: {// Indicate Connection
            Client c;
            c.ip = sender;
            c.port = port;
            c.x = 0;
            c.y = 0;
            connectedClients.push_back(c);
            std::cout << "[pbserverd] New client connected: " << sender << " with port " << port << ".\n";
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)0 << connectedClients[i].ip.toInteger() << connectedClients[i].port; // Client Connected
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] Cannot send Client Connected packet to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;}
        case 1: {// Indicate Disconnection
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip == sender && connectedClients[i].port == port)
                {
                    if (i == 0)
                        connectedClients.erase(connectedClients.begin());
                    else
                        connectedClients.erase(std::next(connectedClients.begin(), i));
                    std::cout << "[pbserverd] Client disconnected: " << sender << " with port " << port << ".\n";
                    break;
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)1 << connectedClients[i].ip.toInteger() << connectedClients[i].port; // Client Disconnected
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] Cannot send Client Disconnected packet to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;}
        case 2: {// Move X and Y
            int x, y;
            packet >> x >> y;
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip == sender && connectedClients[i].port == port)
                {
                    connectedClients[i].x = x;
                    connectedClients[i].y = y;
                    std::cout << "[pbserverd] Movement from " << sender << " with port " << port << " - " << "X: " << x << ", Y: " << y << '\n';
                    break;
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)2 << connectedClients[i].ip.toInteger() << connectedClients[i].x << connectedClients[i].y; // Move X/Y
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] cannot send X/Y data to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;}
        }
    }
    return 0;
}
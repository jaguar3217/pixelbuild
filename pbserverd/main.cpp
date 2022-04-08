#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include "Client.hpp"
#include "states.hpp"

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
                if (connectedClients[i].ip != sender || connectedClients[i].port != port)
                {
                    // Send Client Connected
                    sf::Packet spacket;
                    spacket << (sf::Int8)0 << connectedClients[i].ip.toInteger() << connectedClients[i].port;
                    if (socket.send(spacket, sender, port) != sf::Socket::Done)
                        std::cerr << "[pbserverd] Cannot send Client Connected packet to " << sender << ':' << port << '\n';
                    // Send Move X/Y
                    spacket.clear();
                    spacket << (sf::Int8)2 << connectedClients[i].ip.toInteger() << connectedClients[i].port << connectedClients[i].x << connectedClients[i].y; // Move X/Y
                    if (socket.send(spacket, sender, port) != sf::Socket::Done)
                        std::cerr << "[pbserverd] cannot send X/Y data to " << sender << ':' << port << '\n';
                    // Send Frame
                    spacket.clear();
                    spacket << (sf::Int8)3 << connectedClients[i].ip.toInteger() << connectedClients[i].port << connectedClients[i].frame;
                    if (socket.send(spacket, sender, port) != sf::Socket::Done)
                        std::cerr << "[pbserverd] cannot send frame packets to " << sender << ':' << port << '\n';
                    // Send State
                    spacket << (sf::Int8)4 << connectedClients[i].ip.toInteger() << connectedClients[i].port << connectedClients[i].state;
                    if (socket.send(spacket, sender, port) != sf::Socket::Done)
                        std::cerr << "[pbserverd] cannot send state packets to " << sender << ':' << port << '\n';
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip != sender || connectedClients[i].port != port)
                {
                    sf::Packet spacket;
                    spacket << (sf::Int8)0 << sender.toInteger() << port; // Client Connected
                    if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                        std::cerr << "[pbserverd] Cannot send Client Connected packet to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
                }
                else
                {
                    std::cout << "[pbserverd] Not reached.\n";
                }
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
                spacket << (sf::Int8)1 << sender.toInteger() << port; // Client Disconnected
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
                    //std::cout << "[pbserverd] Movement from " << sender << " with port " << port << " - " << "X: " << x << ", Y: " << y << '\n';
                    break;
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)2 << sender.toInteger() << port << x << y; // Move X/Y
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] cannot send X/Y data to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;}
        case 3: {
            int frame;
            packet >> frame;
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip == sender && connectedClients[i].port == port)
                {
                    connectedClients[i].frame = frame;
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)3 << sender.toInteger() << port << frame;
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] cannot send frame packets to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;
        }
        case 4: {
            int state;
            packet >> state;
            for (int i = 0; i < connectedClients.size(); i++)
            {
                if (connectedClients[i].ip == sender && connectedClients[i].port == port)
                {
                    connectedClients[i].state = state;
                }
            }
            for (int i = 0; i < connectedClients.size(); i++)
            {
                sf::Packet spacket;
                spacket << (sf::Int8)4 << sender.toInteger() << port << state;
                if (socket.send(spacket, connectedClients[i].ip, connectedClients[i].port) != sf::Socket::Done)
                    std::cerr << "[pbserverd] cannot send state packets to " << connectedClients[i].ip << ':' << connectedClients[i].port << '\n';
            }
            break;
        }
        }
    }
    return 0;
}
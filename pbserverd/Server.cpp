#include "Server.hpp"
#include <iostream>

Server::Server() {
    socket.setBlocking(false);
}

Server::~Server() {}

bool Server::loadLevel(const std::string& filePath) {
    sf::FileInputStream file;
    if (!file.open(filePath))
        return false;

    char wh[2];
    file.read(wh, 2);
    levelWidth = wh[0];
    levelHeight = wh[1];
    level.reset(new char[levelWidth * levelHeight]);
    file.read(level.get(), levelWidth * levelHeight);
    return true;
}

void Server::run() {
    if (socket.bind(25635) != sf::Socket::Done) {
        std::cerr << "[Server] Cannot bind to port 25635 (UDP).\n";
        return;
    }
    std::cout << "[Server] Listening on port 25635...\n";

    sf::IpAddress sender;
    unsigned short port;
    sf::Packet packet;

    while (true) {
        if (socket.receive(packet, sender, port) == sf::Socket::Done) {
            sf::Int8 cmd;
            packet >> cmd;
            switch (cmd) {
                case 0: addClient(sender, port); break;
                case 1: removeClient(sender, port); break;
                case 2: {
                    int x, y;
                    packet >> x >> y;
                    setPosition(sender, port, x, y);
                    break;
                }
                case 3: {
                    int frame;
                    packet >> frame;
                    setAnimFrame(sender, port, frame);
                    break;
                }
                case 4: {
                    int state;
                    packet >> state;
                    setState(sender, port, state);
                    break;
                }
            }
        }
    }
}

void Server::addClient(sf::IpAddress sender, unsigned short port) {
    // Create and add the new client to the list
    Client newClient;
    newClient.ip = sender;
    newClient.port = port;
    clients.push_back(newClient);

    // Notify all other clients about the new client
    sf::Packet newClientPacket;
    newClientPacket << sf::Int8(0) /* Client Connected */ << sender.toInteger() << port;
    broadcast(sender, port, newClientPacket);

    // Send all existing clients' states to the new client
    for (const Client& client : clients) {
        if (!(client.ip == sender && client.port == port)) {
            // Send connection state
            sf::Packet connectionPacket;
            connectionPacket << sf::Int8(0) /* Client Connected */ << client.ip.toInteger() << client.port;
            socket.send(connectionPacket, sender, port);

            // Send position
            sf::Packet positionPacket;
            positionPacket << sf::Int8(2) /* Move X/Y */ << client.ip.toInteger() << client.port << client.x << client.y;
            socket.send(positionPacket, sender, port);

            // Send animation frame
            sf::Packet framePacket;
            framePacket << sf::Int8(3) /* Send Frame */ << client.ip.toInteger() << client.port << client.frame;
            socket.send(framePacket, sender, port);

            // Send state
            sf::Packet statePacket;
            statePacket << sf::Int8(4) /* Send State */ << client.ip.toInteger() << client.port << client.state;
            socket.send(statePacket, sender, port);
        }
    }

    // Send Tilemap to the new client
    sendTilemap(sender, port);
}

void Server::sendTilemap(sf::IpAddress recipient, unsigned short port) {
    sf::Packet tilemapPacket;
    tilemapPacket << sf::Int8(5); // Tilemap packet type

    socket.setBlocking(true);  // Temporarily set socket to blocking to ensure tilemap is sent completely
    socket.send(tilemapPacket, recipient, port);

    char wh[2] = {static_cast<char>(levelWidth), static_cast<char>(levelHeight)};
    socket.send(wh, 2, recipient, port);
    socket.send(level.get(), levelWidth * levelHeight, recipient, port);
    socket.setBlocking(false);  // Reset to non-blocking mode
}

void Server::removeClient(sf::IpAddress sender, unsigned short port) {
    int index = findElement(sender, port);
    if (index != -1) {
        clients.erase(clients.begin() + index);
    }

    sf::Packet packet;
    packet << sf::Int8(1) << sender.toInteger() << port;
    broadcast(sender, port, packet);
}

void Server::setPosition(sf::IpAddress sender, unsigned short port, int x, int y) {
    int index = findElement(sender, port);
    if (index != -1) {
        clients[index].x = x;
        clients[index].y = y;
    }

    sf::Packet packet;
    packet << sf::Int8(2) << sender.toInteger() << port << x << y;
    broadcast(sender, port, packet);
}

void Server::setAnimFrame(sf::IpAddress sender, unsigned short port, int frame) {
    int index = findElement(sender, port);
    if (index != -1) {
        clients[index].frame = frame;
    }

    sf::Packet packet;
    packet << sf::Int8(3) << sender.toInteger() << port << frame;
    broadcast(sender, port, packet);
}

void Server::setState(sf::IpAddress sender, unsigned short port, int state) {
    int index = findElement(sender, port);
    if (index != -1) {
        clients[index].state = state;
    }

    sf::Packet packet;
    packet << sf::Int8(4) << sender.toInteger() << port << state;
    broadcast(sender, port, packet);
}

void Server::broadcast(sf::IpAddress sender, unsigned short port, sf::Packet& packet) {
    for (auto& client : clients) {
        if (!(client.ip == sender && client.port == port)) {
            socket.send(packet, client.ip, client.port);
        }
    }
}

int Server::findElement(sf::IpAddress sender, unsigned short port) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].ip == sender && clients[i].port == port) {
            return i;
        }
    }
    return -1;
}

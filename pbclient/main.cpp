#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <pbengine.hpp>
#include <states.hpp>

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    sf::RenderTexture texture;
    sf::UdpSocket socket;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
    if (!texture.create(512, 256, true)) // TODO: Replace with non-deprecated method to enable depth buffer
    {
        std::cerr << "[pbclient] Cannot create sf::RenderTexture\n";
    }
    Engine engine;
    engine.SetTex(&texture);
    std::vector<Player*> plrlist;
    Player npc1;
    Player npc2;
    npc1.load("plrsheet.png");
    npc2.load("plrsheet.png");
    npc1.move(100, 100);
    npc2.move(200, 200);
    plrlist.push_back(&npc1);
    plrlist.push_back(&npc2);
    engine.BindPlrList(plrlist);
    if (argc == 2)
        {
            socket.setBlocking(false);
            sf::Packet packet;
            packet << (sf::Int8)0;
            sf::IpAddress recipient = argv[1];
            if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                std::cerr << "[pbclient] cannot send to IP, exiting\n";
                return 1;
            }
        }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (argc == 2)
                {
                    sf::Packet packet;
                    packet << (sf::Int8)1;
                    sf::IpAddress recipient = argv[1];
                    if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                        std::cerr << "[pbclient] cannot send to IP, exiting\n";
                        return 1;
                    }
                }
                window.close();
            }
        }
        sf::Packet s_packet;
        if (socket.receive(s_packet, sender, port) == sf::Socket::Done)
        {
            sf::Int8 cmd;
            s_packet >> cmd;
            switch (cmd)
            {
            case 0: {
                std::cout << "[pbclient] Packet received: Client Connected\n";
                break;
            }
            case 1: {
                std::cout << "[pbclient] Packet received: Client Disconnected\n";
                break;
            }
            case 2: {
                std::cout << "[pbclient] Packet received: X/Y Movement\n";
                break;
            }
            }
        }
        int state;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            state = PLAYER_UP;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] cannot send to IP, exiting\n";
                    return 1;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            state = PLAYER_LEFT;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] cannot send to IP, exiting\n";
                    return 1;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            state = PLAYER_DOWN;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] cannot send to IP, exiting\n";
                    return 1;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            state = PLAYER_RIGHT;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] cannot send to IP, exiting\n";
                    return 1;
                }
            }
        }
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
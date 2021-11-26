#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <pbengine.hpp>
#include <states.hpp>

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    sf::RenderTexture texture;
    if (!texture.create(512, 256, true)) // enable depth buffer
    {
        std::cerr << "[pbclient] Cannot create sf::RenderTexture\n";
    }
    Engine engine;
    engine.SetTex(&texture);
    sf::UdpSocket socket;
    if (argc == 2)
        {
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
        int state;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            state = PLAYER_UP;
            engine.Move(state);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            state = PLAYER_LEFT;
            engine.Move(state);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            state = PLAYER_DOWN;
            engine.Move(state);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            state = PLAYER_RIGHT;
            engine.Move(state);
        }
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
        window.display();
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
    return 0;
}
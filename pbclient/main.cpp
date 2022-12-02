#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <pbengine.hpp>
#include <states.hpp>

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    bool focused = true;
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
    engine.BindPlrList(plrlist);
    if (argc == 2)
        {
            socket.setBlocking(false);
            sf::Packet packet;
            packet << (sf::Int8)0;
            sf::IpAddress recipient = argv[1];
            socket.send(packet, recipient, 25635);
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
                    socket.send(packet, recipient, 25635);
                }
                window.close();
            }
            if (event.type == sf::Event::GainedFocus) focused = true;
            if (event.type == sf::Event::LostFocus) focused = false;
        }
        sf::Packet s_packet;
        if (socket.receive(s_packet, sender, port) == sf::Socket::Done)
        {
            sf::Int8 cmd;
            s_packet >> cmd;
            sf::Int32 conn_ip_int;
            unsigned short conn_port;
            s_packet >> conn_ip_int >> conn_port;
            sf::IpAddress conn_ip(conn_ip_int);
            if (cmd == 0)
            {
                static Player conn;
                conn.load("plrsheet.png");
                conn.m_ip = conn_ip;
                conn.m_port = conn_port;
                plrlist.push_back(&conn);
                engine.BindPlrList(plrlist);
            }
            if (cmd == 5)
            {
                std::cout << "[pbclient] Received Five\n";
                char level[128];
                socket.setBlocking(true);
                std::size_t received;
                if (socket.receive(level, 128, received, sender, port) != sf::Socket::Done)
                    std::cerr << "[pbclient] [ERROR] Cannot receive tilemap from server\n";
                engine.SetLevel(level);
                socket.setBlocking(false);
            }
            for (int i = 0; i < plrlist.size(); i++)
            {
                if (plrlist[i]->m_ip == conn_ip && plrlist[i]->m_port == conn_port)
                {
                    switch (cmd)
                    {
                    case 1: {
                        if (i == 0)
                            plrlist.erase(plrlist.begin());
                        else
                            plrlist.erase(std::next(plrlist.begin(), i));
                        engine.BindPlrList(plrlist);
                        break;
                    }
                    case 2: {
                        int x, y;
                        s_packet >> x >> y;
                        plrlist[i]->setPosition(x, y);
                        break;
                    }
                    case 3: {
                        int frame;
                        s_packet >> frame;
                        plrlist[i]->increment_frame(frame);
                        break;
                    }
                    case 4: {
                        int state;
                        s_packet >> state;
                        plrlist[i]->look(state);
                        break;
                    }
                    }
                    break;
                }
            }
        }
        int state; bool keyPressed = false;
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && focused)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) state = PLAYER_UP;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) state = PLAYER_LEFT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) state = PLAYER_DOWN;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) state = PLAYER_RIGHT;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                socket.send(packet, recipient, 25635);
                packet.clear();
                packet << (sf::Int8)4 << state;
                socket.send(packet, recipient, 25635);
            }
            keyPressed = true;
        }
        // Send current animation state
        if (argc == 2 && keyPressed)
        {
            sf::Packet packet;
            packet << (sf::Int8)3 << engine.GetFrame();
            sf::IpAddress recepient = argv[1];
            socket.send(packet, recepient, 25635);
        }
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
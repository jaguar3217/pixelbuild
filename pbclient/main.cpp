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
    engine.BindPlrList(plrlist);
    if (argc == 2)
        {
            socket.setBlocking(false);
            sf::Packet packet;
            packet << (sf::Int8)0;
            sf::IpAddress recipient = argv[1];
            if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                std::cerr << "[pbclient] There is packet loss.\n";
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
                        std::cerr << "[pbclient] There is packet loss.\n";
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
            sf::Int32 conn_ip_int;
            unsigned short conn_port;
            s_packet >> conn_ip_int >> conn_port;
            sf::IpAddress conn_ip(conn_ip_int);
            switch (cmd)
            {
            case 0: {
                std::cout << "[pbclient] Packet received: Client Connected\n";
                static Player conn;
                conn.load("plrsheet.png");
                conn.m_ip = conn_ip;
                conn.m_port = conn_port;
                plrlist.push_back(&conn);
                engine.BindPlrList(plrlist);
                break;
            }
            case 1: {
                std::cout << "[pbclient] Packet received: Client Disconnected\n";
                for (int i = 0; i < plrlist.size(); i++)
                {
                    if (plrlist[i]->m_ip == conn_ip || plrlist[i]->m_port == conn_port)
                    {
                        std::cout << "[pbclient] Found.\n";
                        if (i == 0)
                            plrlist.erase(plrlist.begin());
                        else
                            plrlist.erase(std::next(plrlist.begin(), i));
                        engine.BindPlrList(plrlist);
                        break;
                    }
                }
                break;
            }
            case 2: {
                std::cout << "[pbclient] Packet received: X/Y Movement\n";
                int x, y;
                s_packet >> x >> y;
                for (int i = 0; i < plrlist.size(); i++)
                {
                    if (plrlist[i]->m_ip == conn_ip || plrlist[i]->m_port == conn_port)
                    {
                        plrlist[i]->setPosition(x, y);
                        break;
                    }
                }
                break;
            }
            case 3: {
                std::cout << "[pbclient] Packet receied: Update Animation\n";
                int frame;
                s_packet >> frame;
                for (int i = 0; i < plrlist.size(); i++)
                {
                    if (plrlist[i]->m_ip == conn_ip || plrlist[i]->m_port == conn_port)
                    {
                        plrlist[i]->increment_frame(frame);
                        break;
                    }
                }
                break;
            }
            case 4: {
                std::cout << "[pbclient] Packet received: Update State\n";
                int state;
                s_packet >> state;
                for (int i = 0; i < plrlist.size(); i++)
                {
                    if (plrlist[i]->m_ip == conn_ip || plrlist[i]->m_port == conn_port)
                    {
                        plrlist[i]->look(state);
                    }
                }
                break;
            }
            }
        }
        int state; bool keyPressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            state = PLAYER_UP;
            engine.Move(state);
            if (argc == 2)
            {
                sf::Packet packet;
                packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
                sf::IpAddress recipient = argv[1];
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
                packet.clear();
                packet << (sf::Int8)4 << state;
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
            }
            keyPressed = true;
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
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
                packet.clear();
                packet << (sf::Int8)4 << state;
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
            }
            keyPressed = true;
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
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
                packet.clear();
                packet << (sf::Int8)4 << state;
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
            }
            keyPressed = true;
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
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
                packet.clear();
                packet << (sf::Int8)4 << state;
                if (socket.send(packet, recipient, 25635) != sf::Socket::Done) {
                    std::cerr << "[pbclient] There is packet loss.\n";
                }
            }
            keyPressed = true;
        }
        // Send current animation state
        if (argc == 2 && keyPressed)
        {
            sf::Packet packet;
            packet << (sf::Int8)3 << engine.GetFrame();
            sf::IpAddress recepient = argv[1];
            if (socket.send(packet, recepient, 25635) != sf::Socket::Done)
            {
                std::cerr << "[pbclient] There is packet loss.\n";
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
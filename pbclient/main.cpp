#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <pbengine.hpp>
#include <states.hpp>
#include <deque>

class Chat : public sf::Drawable {
private:
	const static int MAX_LINES = 25;
	int linewidth;
	sf::IntRect size;
	sf::Font font;
	sf::Text tempText;
	std::deque<sf::Text> chatlog;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Chat();
	void add_string(std::string s);
};

// Chat.cpp
Chat::Chat() {
	linewidth = 20;

	size.height = 512 / 2;
	size.width = 256 / 2;
	size.top = 0;
	size.left = 0;

	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		// error...
			 //return 0;
	}
	tempText.setFont(font);
	tempText.setCharacterSize(15);
	tempText.setColor(sf::Color::White);
	tempText.setStyle(sf::Text::Bold);
}

void Chat::add_string(std::string s) {
	// Move all other strings one line up.
	for (auto it = chatlog.begin(); it < chatlog.end(); it++) {
		sf::Vector2f temp = it->getPosition();
		temp.y -= linewidth;
		it->setPosition(temp);
	}
	// Add the new string to the bottom of the chat.
	tempText.setString(s);
	int xPos = size.left;
	int yPos = size.top + size.height - linewidth;
	tempText.setPosition(sf::Vector2f(xPos, yPos));
	chatlog.push_back(tempText);

	if (chatlog.size() > MAX_LINES) {
		chatlog.pop_front();
	}
}

void Chat::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto it = chatlog.begin(); it < chatlog.end(); it++) {
		target.draw(*it, states);
	}
}

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    bool focused = true;
    sf::RenderTexture texture;
    sf::UdpSocket socket;
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;
	sf::Clock clock;
    int packets = 0;
	int packetlimit = 0;
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
	sf::String input;
	Chat chat;
	sf::Font font;
	sf::Text chatin;

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	chatin.setFont(font);
	chatin.setCharacterSize(24);
	chatin.setFillColor(sf::Color::White);

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
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) {
					input += static_cast<char>(event.text.unicode);
					chatin.setFillColor(sf::Color::White);
					chatin.setString(input);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter)
				{
					sf::Packet sendpack;
					sendpack << (sf::Int8)5 << input;
					if (argc == 2) {
						sf::IpAddress recipient = argv[1];
						socket.send(sendpack, recipient, 25635);
					}
					input.clear();
				}
			}
            if (event.type == sf::Event::GainedFocus) focused = true;
            if (event.type == sf::Event::LostFocus) focused = false;
        }

		//Chat chat;
		//chat.add_string("HELLO WORLD");
		//chat.add_string("LUCA APOLZAN");
		//chat.add_string("asdfjkl;asdfjkl;!@#$%^&*()_+=-");

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
                plrlist.push_back(new Player());
                Player *conn = plrlist.back();
                conn->load("plrsheet.png");
                conn->m_ip = conn_ip;
                conn->m_port = conn_port;
                engine.BindPlrList(plrlist);
            }
            else if (cmd == 5)
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
			else if (cmd == 6)
			{
				sf::String msg;
				s_packet >> msg;
				chat.add_string(msg);
			}
            else for (int i = 0; i < plrlist.size(); i++)
            {
                if (plrlist[i]->m_ip == conn_ip && plrlist[i]->m_port == conn_port)
                {
                    switch (cmd)
                    {
                    case 1: {
                        plrlist.erase(plrlist.begin() + i);
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
            if (argc == 2 && clock.getElapsedTime().asMilliseconds() > 17)
            {
				if (packets > packetlimit)
				{
					// Send X/Y
					sf::Packet packet;
					packet << (sf::Int8)2 << engine.GetX() << engine.GetY();
					sf::IpAddress recipient = argv[1];
					socket.send(packet, recipient, 25635);

					// Send State
					packet.clear();
					packet << (sf::Int8)4 << state;
					socket.send(packet, recipient, 25635);
					packet.clear();

					// Send Frame
					packet << (sf::Int8)3 << engine.GetFrame();
					sf::IpAddress recepient = argv[1];
					socket.send(packet, recepient, 25635);

					// Reset Packets
					packets = 0;
				}
                
                // Reset Packets / Clock
				//std::cout << "[pbclient] No. of packets: " << std::dec << packets << "; Elapsed Time: " << clock.getElapsedTime().asMilliseconds() << " ms\n";
				packetlimit = packets;
				clock.restart();
            }
            else
                packets += 3; // no. of packets (X/Y, state, frame)
            keyPressed = true;
        }
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
		window.draw(chat);
		window.draw(chatin);
        window.display();
    }
    return 0;
}
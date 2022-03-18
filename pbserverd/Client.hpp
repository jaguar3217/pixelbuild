#include <SFML/Network.hpp>

struct Client {
    sf::IpAddress ip;
    unsigned short port;
    int x = 0;
    int y = 0;
    int frame = 0;
    int state = 0;
};
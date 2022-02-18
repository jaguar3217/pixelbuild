#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <states.hpp>

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player();
    ~Player();
    void look(int state);
    void increment_frame(int frame);
    bool load(const std::string& texfile);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::IpAddress m_ip;
    unsigned short m_port;
private:
    sf::Sprite m_sprite;
    sf::IntRect m_rectResourceSprite;
    sf::Texture m_texture;
    int m_frame = 0;
};
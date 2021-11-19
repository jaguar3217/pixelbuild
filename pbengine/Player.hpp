#pragma once
#include <SFML/Graphics.hpp>
#include <states.hpp>

class Player : public sf::Drawable, public sf::Transformable {
public:
    Player();
    ~Player();
    void look(int state);
    bool load(const std::string& texfile);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite m_sprite;
    sf::IntRect m_rectResourceSprite;
    sf::Texture m_texture;
};
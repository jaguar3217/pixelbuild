#include <SFML/Graphics.hpp>
#include <Player.hpp>

Player::Player()
{
    m_rectResourceSprite.left = 0;
    m_rectResourceSprite.top = 0;
    m_rectResourceSprite.width = 32;
    m_rectResourceSprite.height = 32;
}

Player::~Player()
{

}

bool Player::load(const std::string& texfile)
{
    sf::Texture texture;
    texture.loadFromFile(texfile);
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(m_rectResourceSprite);
    return true;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = m_sprite.getTexture();
}
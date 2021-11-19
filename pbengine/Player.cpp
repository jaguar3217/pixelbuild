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

void Player::look(int state)
{
    m_rectResourceSprite.top = 32 * state;
    m_sprite.setTextureRect(m_rectResourceSprite);
}

bool Player::load(const std::string& texfile)
{
    m_texture.loadFromFile(texfile);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(m_rectResourceSprite);
    return true;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = m_sprite.getTexture();
    target.draw(m_sprite, states);
}
#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <states.hpp>

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

int anim[] = {1, 1, 2, 3, 4, 4, 3, 2};
void Player::increment_frame(int frame)
{
    m_frame = frame % 8;
    m_rectResourceSprite.left = 32 * anim[m_frame];
    m_sprite.setTextureRect(m_rectResourceSprite);
}

int Player::get_frame()
{
    return m_frame;
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <pbengine.hpp>
#include <Player.hpp>

Engine::Engine() {
    std::cout << "[pbengine] Starting...\n";
    // WORSHIP HARUHI!
    m_plr.load("plrsheet.png");
    std::cout << "[pbengine] Started.\n";
}

Engine::~Engine() {
    std::cout << "[pbengine] Deleted.\n";
}

void Engine::SetTex(sf::RenderTexture* texture)
{
    m_texture = texture;
    m_texture->clear();
    m_texture->draw(m_plr);
    m_texture->display();
}

void Engine::Speed(int speed)
{
    m_speed = speed;
}

int Engine::GetSpeed()
{
    return m_speed;
}

void Engine::Move(int state)
{
    if (m_plr.getPosition().x >= 500 && m_plr.getPosition().x <= 502) m_speed += 10;
    if (m_plr.getPosition().y >= 200 && m_plr.getPosition().y <= 202) m_speed -= 10;
    m_plr.look(state);
    switch (state)
    {
        case PLAYER_DOWN:
            m_plr.move(0, m_speed * m_elapsed.asSeconds());
            break;
        case PLAYER_UP:
            m_plr.move(0, -m_speed * m_elapsed.asSeconds());
            break;
        case PLAYER_LEFT:
            m_plr.move(-m_speed * m_elapsed.asSeconds(), 0);
            break;
        case PLAYER_RIGHT:
            m_plr.move(m_speed * m_elapsed.asSeconds(), 0);
            break;
    }
}

void Engine::Render()
{
    m_elapsed = m_clock.getElapsedTime();
    m_clock.restart();
    m_texture->clear();
    m_texture->draw(m_plr);
    m_texture->display();
}
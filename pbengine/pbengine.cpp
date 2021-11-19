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

void Engine::Move(int state)
{
    switch (state)
    {
        case PLAYER_DOWN:
            m_plr.move(0, 1);
            break;
        case PLAYER_UP:
            m_plr.move(0, -1);
            break;
        case PLAYER_LEFT:
            m_plr.move(-1, 0);
            break;
        case PLAYER_RIGHT:
            m_plr.move(1, 0);
            break;
    }
}

void Engine::Render()
{
    m_texture->clear();
    m_texture->draw(m_plr);
    m_texture->display();
}
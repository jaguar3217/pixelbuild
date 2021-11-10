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
}

void Engine::Render()
{
}
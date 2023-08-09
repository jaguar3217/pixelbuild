#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstring>
#include <pbengine.hpp>
#include <Player.hpp>

Engine::Engine() {
    std::cout << "[pbengine] Starting...\n";
    m_plr.load("plrsheet.png");
    m_level = new char[16 * 8];
    m_levelW = 16;
    m_levelH = 8;
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

void Engine::SetLevel(char level[])
{
    for (int i = 0; i < m_levelW * m_levelH; i++)
    {
        std::cout << std::hex << (int)level[i] << ' ';
        m_level[i] = level[i];
    }

    if (!m_tilemap.load("tileset.png", sf::Vector2u(32, 32), m_level, m_levelW, m_levelH))
        std::cerr << "[pbengine] [ERROR] Cannot Load Tilemap Texture\n";
}

void Engine::SetMapSize(int width, int height)
{
    // Set new width & height
    m_level = new char[width * height];
    m_levelW = width;
    m_levelH = height;
}

void Engine::BindPlrList(std::vector<Player*> plrlist)
{
    m_plrlist = plrlist;
}

void Engine::Speed(int speed)
{
    m_speed = speed;
}

int Engine::GetSpeed()
{
    return m_speed;
}

int Engine::GetX()
{
    return m_plr.getPosition().x;
}

int Engine::GetY()
{
    return m_plr.getPosition().y;
}

int Engine::GetFrame()
{
    return m_plr.get_frame();
}

sf::Vector2i Engine::GetTileMapOffset()
{
	return sf::Vector2i(m_tilemap.getPosition());
}

void Engine::Move(int state)
{
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
    m_plr.increment_frame(m_speed / 10 * m_elapsed_global.asSeconds());
}

void Engine::HidePlayer()
{
	m_showPlayer = false;
}

void Engine::ShowPlayer()
{
	m_showPlayer = true;
}

void Engine::MoveTileMap(int ox, int oy)
{
	m_tilemap.move(ox, oy);
}

void Engine::Render()
{
    int r = 0;
    m_elapsed = m_clock.getElapsedTime();
    m_elapsed_global = m_clock_global.getElapsedTime();
    m_clock.restart();
    m_texture->clear();
    m_texture->draw(m_tilemap);
    for (int i = 0; i < m_plrlist.size(); i++) {
        //m_plrlist[i]->setPosition(rand() % 512, rand() % 256);
        m_texture->draw(*m_plrlist[i]);
        r++;
    }
    if (m_showPlayer)
		m_texture->draw(m_plr);
    m_texture->display();
    r = 0;
}
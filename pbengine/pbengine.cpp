#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <pbengine.hpp>

void Engine::Init() {
}

void Engine::SetTex(sf::RenderTexture* texture)
{
    m_texture = texture;
}

void Engine::Render()
{
    m_texture->clear();
    sf::Font font;
    #ifdef _WIN32
    if (!font.loadFromFile("C:/Windows/Fonts/comicbd.ttf")) {
        std::cerr << "[pbengine] cannot load comicbd.ttf (Windows)" << std::endl;
    }
    #endif
    #ifdef linux
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/comicbd.ttf")) {
        std::cerr << "[pbengine] cannot load comicbd.ttf (Linux)" << std::endl;
    }
    #endif
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Underlined);
    m_texture->draw(text);
    m_texture->display();
}
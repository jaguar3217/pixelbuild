#pragma once

#include "wxSFMLCanvas.hpp"
#include "pbengine.hpp"

class GamePreview : public wxSFMLCanvas
{
public:
    GamePreview(wxWindow* Parent,
        wxWindowID ID,
        wxPoint& Position,
        wxSize& Size,
        long       Style = 0) :
        wxSFMLCanvas(Parent, ID, Position, Size, Style)
    {
        // set up the circle
        rectangle.setSize(sf::Vector2f(512.f, 256.f));
        rectangle.setFillColor(sf::Color::Yellow);

        // set up the texture
        if (!m_texture.create(512, 256, true))
        {
            std::cerr << "[pbeditor] Cannot create sf::RenderTexture\n";
        }

        // set up the sprite
        m_sprite.setTexture(engineOut);

        // configure the engine
        m_engine.SetTex(&m_texture);
    }

private:
    virtual void OnUpdate();

    sf::RectangleShape rectangle;
    sf::RenderTexture m_texture;
    const sf::Texture& engineOut = m_texture.getTexture();
    sf::Sprite m_sprite;
    Engine m_engine;
};
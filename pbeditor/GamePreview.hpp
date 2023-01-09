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
		long       Style = 0);

private:
    virtual void OnUpdate();

    sf::RenderTexture m_texture;
    const sf::Texture& engineOut = m_texture.getTexture();
    sf::Sprite m_sprite;
    Engine m_engine;
};
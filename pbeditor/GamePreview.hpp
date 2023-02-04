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

	void SetTileToPaint(int tile);

private:
    virtual void OnUpdate();

	int m_currentTile = 0;
	char m_level[16 * 8];

    sf::RenderTexture m_texture;
    const sf::Texture& engineOut = m_texture.getTexture();
    sf::Sprite m_sprite;
    Engine m_engine;
};
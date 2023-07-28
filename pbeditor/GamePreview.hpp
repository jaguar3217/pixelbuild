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
	void OpenNewFile(wxString path);
	void SetMapSize(int width, int height);
	char* GetLevel();

private:
    virtual void OnUpdate();

	int m_currentTile = 0;
	char* m_level;
	int m_levelW, m_levelH;

    sf::RenderTexture m_texture;
    const sf::Texture& engineOut = m_texture.getTexture();
    sf::Sprite m_sprite;
    Engine m_engine;
};
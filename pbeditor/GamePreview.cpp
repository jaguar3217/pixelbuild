#include "GamePreview.hpp"

GamePreview::GamePreview(wxWindow * Parent, wxWindowID ID, wxPoint & Position, wxSize & Size, long Style) :
	wxSFMLCanvas(Parent, ID, Position, Size, Style)
{
	// set cursor to paintbrush
	this->SetCursor(wxCursor(wxCURSOR_PAINT_BRUSH));

	// set up the texture
	if (!m_texture.create(512, 256, true))
	{
		std::cerr << "[pbeditor] Cannot create sf::RenderTexture\n";
	}

	// hide the player
	m_engine.HidePlayer();

	// set up the sprite
	m_sprite.setTexture(engineOut);

	// configure the engine
	m_engine.SetTex(&m_texture);

	// load the m_level into the tilemap
	sf::FileInputStream levelFile;
	if (levelFile.open("main.pblvl"))
		levelFile.read(m_level, 128);
	m_engine.SetLevel(m_level);
}

void GamePreview::SetTileToPaint(int tile)
{
	m_currentTile = tile;
}

void GamePreview::OpenNewFile(wxString path)
{
	sf::FileInputStream levelFile;
	if (levelFile.open(path.ToStdString()))
		levelFile.read(m_level, 128);
	m_engine.SetLevel(m_level);
}

char* GamePreview::GetLevel()
{
	return m_level;
}

int lmx = 0, lmy = 0;

void GamePreview::OnUpdate()
{
	// Handle input events
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseInside())
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				m_level[relativePosition().x / 32 + relativePosition().y / 32 * 16] = m_currentTile;
				m_engine.SetLevel(m_level);
			}
			else
			{
				m_engine.MoveTileMap(lmx - relativePosition().x, lmy - relativePosition().y);

				lmx = relativePosition().x;
				lmy = relativePosition().y;
			}
		}
	}

    // Clear the view
    clear();

    // Render engine output
    m_engine.Render();

    // Draw engine render output
    draw(m_sprite);
}
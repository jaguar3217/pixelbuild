#include "GamePreview.hpp"

GamePreview::GamePreview(wxWindow * Parent, wxWindowID ID, wxPoint & Position, wxSize & Size, long Style) :
	wxSFMLCanvas(Parent, ID, Position, Size, Style)
{
	// define level variables
	m_level = new char[16 * 8];
	m_levelW = 16;
	m_levelH = 8;

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

void GamePreview::SetMapSize(int width, int height)
{
	// Tell engine to set map size
	m_engine.SetMapSize(width, height);
	
	// Transfer to old level and reinitalize
    char oldlevel[m_levelW * m_levelH];
	for (int i = 0; i < m_levelW * m_levelH; i++)
	{
		oldlevel[i] = m_level[i];
		std::cout << std::hex << (int)oldlevel[i] << ' ';
	}
	std::cout << std::endl;
    m_level = new char[width * height];

    // Transfer to new level with specified coordinates
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			if (i >= m_levelW || j >= m_levelH)
				m_level[j * width + i] = 1;
            else
                m_level[j * width + i] = oldlevel[j * m_levelW + i];

	// Update width & height
	m_levelW = width;
	m_levelH = height;

	// Set new level
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
				m_level[(relativePosition().x - m_engine.GetTileMapOffset().x) / 32 + (relativePosition().y - m_engine.GetTileMapOffset().y) / 32 * m_levelW] = m_currentTile;
				m_engine.SetLevel(m_level);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			m_engine.MoveTileMap(relativePosition().x - lmx, relativePosition().y - lmy);
		}
	}

    // Clear the view
    clear();

    // Render engine output
    m_engine.Render();

    // Draw engine render output
    draw(m_sprite);

	// Update last mouse position
	lmx = relativePosition().x;
	lmy = relativePosition().y;
}
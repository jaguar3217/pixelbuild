#include "GamePreview.hpp"

GamePreview::GamePreview(wxWindow * Parent, wxWindowID ID, wxPoint & Position, wxSize & Size, long Style) :
	wxSFMLCanvas(Parent, ID, Position, Size, Style)
{
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

void GamePreview::OnUpdate()
{
    // Clear the view
    clear();

    // Render and draw engine output
    m_engine.Render();

    // Draw the circle & engine render output
    draw(m_sprite);
}
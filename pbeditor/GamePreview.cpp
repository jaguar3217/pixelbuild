#include "GamePreview.hpp"

void GamePreview::OnUpdate()
{
    // Clear the view
    clear(sf::Color(255, 0, 0));

    // Render and draw engine output
    m_engine.Render();

    // Draw the circle & engine render output
    draw(rectangle);
    draw(m_sprite);
}
#include "GamePreview.hpp"

void GamePreview::OnUpdate()
{
    // Clear the view
    clear();

    // Render and draw engine output
    m_engine.Render();

    // Draw the circle & engine render output
    draw(m_sprite);
}
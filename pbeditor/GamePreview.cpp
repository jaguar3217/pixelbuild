#include "GamePreview.hpp"

void GamePreview::OnUpdate()
{
    // Clear the view
    clear(sf::Color(255, 0, 0));

    // Draw the circle
    draw(rectangle);
}
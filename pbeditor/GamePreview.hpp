#pragma once

#include "wxSFMLCanvas.hpp"

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
    }

private:
    virtual void OnUpdate();

    sf::RectangleShape rectangle;
};
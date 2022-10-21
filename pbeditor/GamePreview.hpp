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
        circle.setRadius(100.f);
        circle.setFillColor(sf::Color::Yellow);
    }

private:
    virtual void OnUpdate();

    sf::CircleShape circle;
};
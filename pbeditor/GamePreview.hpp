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
        // do nothing
    }

private:
    virtual void OnUpdate();
};
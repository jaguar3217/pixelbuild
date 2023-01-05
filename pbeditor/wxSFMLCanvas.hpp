#pragma once

#include <SFML/Graphics.hpp>
#include <wx/wx.h>

class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID ID = -1,
        const wxPoint& Position = wxDefaultPosition,
        const wxSize& Size = wxDefaultSize, long Style = 0);
    virtual ~wxSFMLCanvas();

private:
    virtual void OnUpdate();
    void OnIdle(wxIdleEvent&);
    void OnPaint(wxPaintEvent&);
    void OnEraseBackground(wxEraseEvent&);

    bool mouseInside();
    sf::Vector2i relativePosition();

    DECLARE_EVENT_TABLE()
};
#pragma once

#include "GamePreview.hpp"

class GamePanel : public wxPanel
{
public:
	GamePanel(wxWindow* Parent,
        wxWindowID ID,
        wxPoint Position,
        wxSize Size,
        long       Style = 0) :
        wxPanel(Parent, ID, Position, Size, Style)
	{
        new GamePreview(this, wxID_ANY, Position, Size);
	}
};

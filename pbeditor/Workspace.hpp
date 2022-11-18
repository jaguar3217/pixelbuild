#pragma once
#include "GameWindow.hpp"

class Workspace : public wxMDIParentFrame
{
public:
	Workspace() :
		wxMDIParentFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(800, 600))
	{
		GameWindow* gw = new GameWindow(this, "Untitled Project");
		gw->Show(true);
	}
};
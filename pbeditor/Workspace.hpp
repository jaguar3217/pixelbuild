#pragma once
#include "GamePanel.hpp"
#include "TileSelector.hpp"

#include <wx/aui/aui.h>
#include <wx/file.h>

class Workspace : public wxFrame
{
public:
	Workspace();

	~Workspace();

private:
	wxAuiManager m_mgr;

	wxFile tileset;
};
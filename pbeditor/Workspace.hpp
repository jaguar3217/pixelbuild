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
	wxMenuBar* m_MenuBar;
	wxAuiManager m_mgr;
	wxFile tileset;

	GamePanel* m_gp;

	void OnMenuNew(wxCommandEvent &evt);
	void OnMenuOpen(wxCommandEvent &evt);
	void OnMenuSave(wxCommandEvent &evt);
	void OnMenuExit(wxCommandEvent &evt);
	void OnMenuSetMapSize(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};
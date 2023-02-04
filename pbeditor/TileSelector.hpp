#pragma once

#include <wx/wx.h>
#include "GamePanel.hpp"
//#include <wx/file.h>

class TileSelector : public wxPanel
{
public:
	TileSelector(wxFrame* Parent, GamePanel* Panel);

	void OnClick(wxCommandEvent& evt);

private:
	GamePanel* m_panel;
};
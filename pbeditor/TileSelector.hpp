#pragma once

#include <wx/wx.h>
//#include <wx/file.h>

class TileSelector : public wxPanel
{
public:
	TileSelector(wxFrame* Parent);

	void OnClick(wxCommandEvent& evt);
};
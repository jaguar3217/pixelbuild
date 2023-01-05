#include "TileSelector.hpp"

TileSelector::TileSelector(wxFrame* Parent) :
	wxPanel(Parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150))
{
	this->SetSize(FromDIP(400), FromDIP(150)); // resize for High DPI screens

		wxInitAllImageHandlers();

		// Get current path
		wxString curPath(wxGetCwd());

		wxImage img = wxImage(curPath + "/tileset.png", wxBITMAP_TYPE_PNG);
		wxBitmap bmp(img);

		/*wxBitmapButton* test = new wxBitmapButton(this, wxID_ANY, bmp, wxPoint(0, 0),
			wxSize(100, 100), wxBORDER_NONE);
		test->SetDefault();*/

		for (int i = 0; i < bmp.GetWidth() / 32; i++)
		{
			wxBitmap newBitmap = bmp.GetSubBitmap(wxRect(i * 32, 0, 32, 32));
			wxBitmapButton* btn = new wxBitmapButton(this, wxID_ANY, newBitmap,
				wxPoint(i * 32, 0), wxSize(32, 32));
			btn->Bind(wxEVT_BUTTON, &TileSelector::OnClick, this);
			btn->SetDefault();
		}
}

void TileSelector::OnClick(wxCommandEvent& evt)
{
	wxMessageBox("Button clicked.", "Test", wxOK | wxICON_INFORMATION);
}
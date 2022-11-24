#pragma once
#include "GamePanel.hpp"

#include <wx/aui/aui.h>

class Workspace : public wxFrame
{
public:
	Workspace() :
		wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(800, 600))
	{
		this->SetSize(FromDIP(800), FromDIP(600)); // resize for High DPI screens

		// notify wxAUI which frame to use
		m_mgr.SetManagedWindow(this);

		// create several UI elements
		/*wxTextCtrl* gp = new wxTextCtrl(this, -1, _("Main content window"),
			wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
			wxNO_BORDER | wxTE_MULTILINE);*/
		wxAuiNotebook* nbook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
			wxSize(512, 256));

		GamePanel* gp = new GamePanel(nbook, wxID_ANY, wxDefaultPosition, wxSize(512, 256));

		nbook->AddPage(gp, "Untitled Project");

		wxTextCtrl* tsel = new wxTextCtrl(this, -1, _("Tile selection"),
			wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
			wxNO_BORDER | wxTE_MULTILINE);

		wxTextCtrl* pexp = new wxTextCtrl(this, -1, _("Project explorer"),
			wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
			wxNO_BORDER | wxTE_MULTILINE);

		wxTextCtrl* prop = new wxTextCtrl(this, -1, _("Properties selector"),
			wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
			wxNO_BORDER | wxTE_MULTILINE);

		// add the panes to the manager
		m_mgr.AddPane(tsel, wxLEFT, wxT("Tiles"));
		m_mgr.AddPane(nbook, wxCENTER);
		m_mgr.AddPane(pexp, wxRIGHT, wxT("Project Explorer"));
		m_mgr.AddPane(prop, wxRIGHT, wxT("Properties"));

		// tell the manager to "commit" all the changes just made
		m_mgr.Update();
	}

	~Workspace()
	{
		m_mgr.UnInit();
	}

private:
	wxAuiManager m_mgr;
};
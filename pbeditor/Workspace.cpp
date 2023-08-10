#include "Workspace.hpp"
#include <wx/tokenzr.h>

wxBEGIN_EVENT_TABLE(Workspace, wxFrame)
EVT_MENU(10001, Workspace::OnMenuNew)
EVT_MENU(10002, Workspace::OnMenuOpen)
EVT_MENU(10003, Workspace::OnMenuSave)
EVT_MENU(10004, Workspace::OnMenuExit)
EVT_MENU(10005, Workspace::OnMenuSetMapSize)
wxEND_EVENT_TABLE()

Workspace::Workspace() :
	wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(1200, 600))
{
	this->SetSize(FromDIP(1200), FromDIP(600)); // resize for High DPI screens

	// Add a menu bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	// Add Menu for file operations
	wxMenu *menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	// Add File Menu to Menu Bar
	m_MenuBar->Append(menuFile, "File");

	// Add Menu for game operations
	wxMenu *menuGame = new wxMenu();
	menuGame->Append(10005, "Set Map Size");

	// Add Game Menu to Menu bar
	m_MenuBar->Append(menuGame, "Game");

	// notify wxAUI which frame to use
	m_mgr.SetManagedWindow(this);

	// open tileset file
	tileset.Open(wxGetCwd() + "/tileset.png");

	// create several UI elements
	wxAuiNotebook* nbook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
		wxSize(512, 256));

	m_gp = new GamePanel(nbook, wxID_ANY, wxDefaultPosition, FromPhys(wxSize(512, 256)));

	nbook->AddPage(m_gp, "Scene View");

	/*wxTextCtrl* tsel = new wxTextCtrl(this, -1, _("Tile selection"),
		wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
		wxNO_BORDER | wxTE_MULTILINE);*/
	TileSelector* tsel = new TileSelector(this, m_gp);

	wxTextCtrl* scn = new wxTextCtrl(this, -1, _("Scene explorer"),
		wxDefaultPosition, wxSize(FromDIP(400), FromDIP(150)),
		wxNO_BORDER | wxTE_MULTILINE);

	wxTextCtrl* pexp = new wxTextCtrl(this, -1, _("Project explorer"),
		wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
		wxNO_BORDER | wxTE_MULTILINE);

	wxTextCtrl* prop = new wxTextCtrl(this, -1, _("Properties selector"),
		wxDefaultPosition, wxSize(FromDIP(200), FromDIP(150)),
		wxNO_BORDER | wxTE_MULTILINE);

	// add the panes to the manager
	m_mgr.AddPane(tsel, wxLEFT, wxT("Tiles"));
	m_mgr.AddPane(scn, wxLEFT, wxT("Scenes"));
	m_mgr.AddPane(nbook, wxCENTER);
	m_mgr.AddPane(pexp, wxRIGHT, wxT("Project Explorer"));
	m_mgr.AddPane(prop, wxRIGHT, wxT("Properties"));

	// tell the manager to "commit" all the changes just made
	m_mgr.Update();
}

Workspace::~Workspace()
{
	m_mgr.UnInit();
}

void Workspace::OnMenuNew(wxCommandEvent & evt)
{
	// Create the main window
	Workspace* MainFrame = new Workspace;
	MainFrame->Show();

	// Close current window
	//Close();
	
	evt.Skip();
}

void Workspace::OnMenuOpen(wxCommandEvent & evt)
{
	wxFileDialog dlg(this, "Open Pixelbuild Level File", "", "", ".pblvl Files (*.pblvl)|*.pblvl", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_gp->OpenNewFile(dlg.GetPath());
	}

	evt.Skip();
}

void Workspace::OnMenuSave(wxCommandEvent & evt)
{
	wxFileDialog dlg(this, "Save Pixelbuild Level File", "", "", ".pblvl Files (*.pblvl)|*.pblvl", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxFile file(dlg.GetPath(), wxFile::write);
		char* level = m_gp->GetLevel();
		int width = m_gp->GetMapWidth();
		int height = m_gp->GetMapHeight();
		char wh[2] = { width, height };
		file.Write(wh, 2);
		file.Write(level, width * height);
		file.Close();
	}
}

void Workspace::OnMenuExit(wxCommandEvent & evt)
{
	Close();
	evt.Skip();
}

void Workspace::OnMenuSetMapSize(wxCommandEvent & evt)
{
	wxTextEntryDialog dlg(this, "Enter with and height seperated by one space:", "Set Map Size");
	if (dlg.ShowModal() == wxID_OK)
	{
		wxStringTokenizer tokenizer(dlg.GetValue(), " ");
		int width = wxAtoi(tokenizer.GetNextToken());
		int height = wxAtoi(tokenizer.GetNextToken());
		m_gp->SetMapSize(width, height);
	}
}

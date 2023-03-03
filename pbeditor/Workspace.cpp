#include "Workspace.hpp"

wxBEGIN_EVENT_TABLE(Workspace, wxFrame)
EVT_MENU(10001, Workspace::OnMenuNew)
EVT_MENU(10002, Workspace::OnMenuOpen)
EVT_MENU(10003, Workspace::OnMenuSave)
EVT_MENU(10004, Workspace::OnMenuExit)
wxEND_EVENT_TABLE()

Workspace::Workspace() :
	wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(800, 600))
{
	this->SetSize(FromDIP(800), FromDIP(600)); // resize for High DPI screens

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
		file.Write(level, 16 * 8);
		file.Close();
	}
}

void Workspace::OnMenuExit(wxCommandEvent & evt)
{
	Close();
	evt.Skip();
}

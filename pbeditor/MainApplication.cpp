#include <SFML/Graphics.hpp>
#include <wx/wx.h>

class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition,
        const wxSize& Size = wxDefaultSize, long Style = 0);
    virtual ~wxSFMLCanvas();
};

wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style) :
    wxControl(Parent, Id, Position, Size, Style) {
    sf::RenderWindow::create(GetHandle());
}

wxSFMLCanvas::~wxSFMLCanvas() {
}

class cMain : public wxFrame
{
    wxButton* m_btn1 = nullptr;
    wxSFMLCanvas* mycanv = nullptr;
    wxDECLARE_EVENT_TABLE();
public:
    cMain();
    void onBtnClicked(wxCommandEvent& evt);
};


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, onBtnClicked)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Window", wxPoint(30, 30), wxSize(800, 600)) {
    mycanv = new wxSFMLCanvas(this, wxID_ANY, wxPoint(50, 50), wxSize(700, 500));
    m_btn1 = new wxButton(this, 10001, "button1", wxPoint(10, 10), wxSize(100, 50));
}

void cMain::onBtnClicked(wxCommandEvent& evt) {
    sf::CircleShape circ(50.0f);
    circ.setOrigin(50.0f, 50.0f);
    circ.setFillColor(sf::Color::Blue);
    circ.setPosition(350, 250);
    mycanv->draw(circ);
    mycanv->display();
}

class myApp : public wxApp
{
    cMain* m_Frame1 = nullptr;
public:
    myApp();
    virtual bool OnInit();
};
wxIMPLEMENT_APP(myApp);

myApp::myApp() {

}

bool myApp::OnInit() {
    // Create the main window
    m_Frame1 = new cMain;
    m_Frame1->Show();
    return true;
}
// TODO: Clean the code and then separate the classes into separate files

#include <SFML/Graphics.hpp>
#include <wx/wx.h>

class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID ID = -1,
        const wxPoint& Position = wxDefaultPosition,
        const wxSize& Size = wxDefaultSize, long Style = 0);
    virtual ~wxSFMLCanvas();

private:
    virtual void OnUpdate();
    void OnIdle(wxIdleEvent&);
    void OnPaint(wxPaintEvent&);
    void OnEraseBackground(wxEraseEvent&); // somehow unused

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
    EVT_IDLE(wxSFMLCanvas::OnIdle)
    EVT_PAINT(wxSFMLCanvas::OnPaint)
END_EVENT_TABLE()

void wxSFMLCanvas::OnIdle(wxIdleEvent&)
{
    // Send a paint message when the control is idle, to ensure maximum framerate
    //Refresh();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent&)
{
    // Prepare the control to be repainted
    wxPaintDC DC(this);

    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}

void wxSFMLCanvas::OnUpdate()
{
}

wxSFMLCanvas::~wxSFMLCanvas()
{}

#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <wx/gtk/win_gtk.h>
#endif

wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position,
    const wxSize& Size, long Style) :
    wxControl(Parent, Id, Position, Size, Style)
{
#ifdef __WXGTK__

    // GTK implementation requires to go deeper to find the
    // low-level X11 identifier of the widget
    gtk_widget_realize(m_wxwindow);
    gtk_widget_set_double_buffered(m_wxwindow, false);
    GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
    XFlush(GDK_WINDOW_XDISPLAY(Win));
    sf::RenderWindow::Create(GDK_WINDOW_XWINDOW(Win));

#else

    // Tested under Windows XP only (should work with X11
    // and other Windows versions - no idea about MacOS)
    sf::RenderWindow::create(GetHandle());

#endif
}

class GamePreview : public wxSFMLCanvas
{
public:

    GamePreview(wxWindow* Parent,
        wxWindowID ID,
        wxPoint& Position,
        wxSize& Size,
        long       Style = 0) :
        wxSFMLCanvas(Parent, ID, Position, Size, Style)
    {
        // do nothing
    }

private:

    virtual void OnUpdate()
    {
        // Clear the view
        clear(sf::Color(255, 0, 0));
    }

    sf::Image  myImage;
    sf::Sprite mySprite;
};

class Workspace : public wxFrame
{
public:

    Workspace() :
        wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(612, 356))
    {
        new GamePreview(this, wxID_ANY, wxPoint(50, 50), wxSize(512, 256));
    }
};

class MainApplication : public wxApp
{
private:

    virtual bool OnInit()
    {
        // Create the main window
        Workspace* MainFrame = new Workspace;
        MainFrame->Show();

        return true;
    }
};

IMPLEMENT_APP(MainApplication);
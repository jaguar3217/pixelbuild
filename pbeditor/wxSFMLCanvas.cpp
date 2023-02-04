#include "wxSFMLCanvas.hpp"

void wxSFMLCanvas::OnIdle(wxIdleEvent&)
{
    // Send a paint message when the control is idle, to ensure maximum framerate
    Refresh(); // somehow screen flickering, debug build maybe [shrug]
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

// Here is the code that fixes the flicker. Life is saved.
void wxSFMLCanvas::OnEraseBackground(wxEraseEvent&)
{
}

void wxSFMLCanvas::OnUpdate()
{
    // Handle to-be-rendered stuff
}

wxSFMLCanvas::~wxSFMLCanvas()
{
}

#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
//#include <wx/gtk/win_gtk.h>
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
    /*GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
    XFlush(GDK_WINDOW_XDISPLAY(Win));*/
    GdkWindow* Win = gtk_widget_get_window((GtkWidget*)GetHandle());
    XFlush(GDK_WINDOW_XDISPLAY(Win));

    sf::RenderWindow::create(GDK_WINDOW_XID(Win));

#else

    // Tested under Windows XP only (should work with X11
    // and other Windows versions - no idea about MacOS)
    sf::RenderWindow::create(GetHandle());

#endif
}

bool wxSFMLCanvas::mouseInside()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::Vector2i canvasPos = this->getPosition();
    sf::Vector2u canvasSize = this->getSize();

    if (mousePos.x >= canvasPos.x && mousePos.y >= canvasPos.y &&
        mousePos.x <= (canvasPos.x + canvasSize.x) &&
        mousePos.y <= (canvasPos.y + canvasSize.y))
        return true;
    else
        return false;
}

sf::Vector2i wxSFMLCanvas::relativePosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::Vector2i canvasPos = this->getPosition();

    return mousePos - canvasPos;
}

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
EVT_IDLE(wxSFMLCanvas::OnIdle)
EVT_PAINT(wxSFMLCanvas::OnPaint)
EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()

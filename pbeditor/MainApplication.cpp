#include "Workspace.hpp"

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
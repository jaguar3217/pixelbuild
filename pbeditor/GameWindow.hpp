#pragma once

#include "GamePanel.hpp"

class GameWindow : public wxMDIChildFrame
{
public:

    GameWindow(wxMDIParentFrame* Parent,
        wxString Name) :
        wxMDIChildFrame(Parent, wxID_ANY, Name, wxDefaultPosition, wxSize(512, 256))
        // TODO: Window size should be proportional to GamePanel
    {
        GamePanel* gp = new GamePanel(this, wxID_ANY, wxPoint(0, 0), wxSize(512, 256));

        wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        this->SetSizer(sizer);

        sizer->Add(gp, 1, wxALIGN_CENTER);

        this->SetSizer(sizer);
        sizer->SetSizeHints(this);
    }
};
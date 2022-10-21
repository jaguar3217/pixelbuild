#pragma once

#include "GamePreview.hpp"

class Workspace : public wxFrame
{
public:

    Workspace() :
        wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(612, 356))
    {
        new GamePreview(this, wxID_ANY, wxPoint(50, 50), wxSize(512, 256));
        new wxButton(this, 10001, "DmyButton", wxPoint(10, 10), wxSize(100, 50));
    }
};
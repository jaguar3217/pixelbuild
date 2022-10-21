#pragma once

#include "GamePreview.hpp"

class Workspace : public wxFrame
{
public:

    Workspace() :
        wxFrame(NULL, wxID_ANY, "Pixelbuild Editor", wxDefaultPosition, wxSize(555, 295))
    {
        new GamePreview(this, wxID_ANY, wxPoint(50, 50), wxSize(512, 256));
    }
};
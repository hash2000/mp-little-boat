#pragma once
#include <FL/Fl_Window.H>
#include "Controls/Toolbars/ToolbarGlobalApps.h"

class MainFrame : public Fl_Window
{
public:
	MainFrame();

private:
	ToolbarGlobalApps _toolbarGlobalApps;
};

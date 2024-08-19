#pragma once
#include <FL/Fl_Overlay_Window.H>
#include "Controls/Toolbars/Toolbar.h"
#include "Controls/Toolbars/ToolButton.h"

class MainFrame : public Fl_Window
{
public:
	MainFrame();

private:
	Toolbar* _toolbar;
	ToolButton* _toolNew;
};

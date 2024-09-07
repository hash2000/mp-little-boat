#pragma once
#include <FL/Fl_Window.H>
#include "Controls/Toolbars/Toolbar.h"

class MainFrame : public Fl_Window
{
public:
	MainFrame();

private:
	Toolbar _toolbar{ 0, 0, w(), 40 };
};

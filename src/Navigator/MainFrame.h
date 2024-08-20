#pragma once
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include "Controls/Toolbars/Toolbar.h"
#include "Controls/Toolbars/ToolButton.h"
#include "Resources/Icons.h"

class MainFrame : public Fl_Window
{
public:
	MainFrame();

private:
	Toolbar _toolbar;
	ToolButton _toolNew;
	Fl_Pixmap _picNew{ NEW_XPM };
};

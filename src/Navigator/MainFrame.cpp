#include <pch.h>
#include "MainFrame.h"
#include "Resources/Icons/16x16/new.h"

MainFrame::MainFrame()
	: Fl_Window(720, 648, "Navigator")
{
	auto wx = 0;
	auto wy = 0;
	auto ww = w();
	auto wh = h();

	_toolbar = new Toolbar(wx, wy, ww, 30);
	_toolNew = new ToolButton(0, 0, 28, 28);
	_toolNew->tooltip("New");
	//_toolNew->image(BLANK_ICON(Fl_Pixmap(NEW_XPM));
	_toolNew->take_focus();

	_toolbar->end();
	_toolbar->activate();

}

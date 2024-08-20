#include <pch.h>
#include "MainFrame.h"

MainFrame::MainFrame()
	: Fl_Window(720, 648, "Navigator")
	, _toolbar(0, 0, 40, h())
	, _toolNew(0, 0, 38, 38)
{
	_toolNew.image(&_picNew);
}

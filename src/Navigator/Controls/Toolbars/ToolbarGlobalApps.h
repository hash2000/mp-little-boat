#pragma once
#include "Toolbar.h"
#include "Controls/Toolbars/ToolButton.h"

class ToolbarGlobalApps : public Toolbar
{
public:
	ToolbarGlobalApps();

private:
	ToolButton _toolNew{ 0, 0, 0, 0, "New"};
	Fl_Button _testButton{ 0, 0, 10, 10, "test"};

	Fl_End _end;
};

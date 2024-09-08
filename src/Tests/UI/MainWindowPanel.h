#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"

class MainWindowPanel : public Fl_Window
{
public:
	MainWindowPanel() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		begin();
		auto panel = new Panel(0, 0, 300, h(), Docking::Left);
		{
			//panel->box(FL_UP_BOX);


			panel->end();
		}
		end();
	}
};

#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"

class MainWindowPanel : public Fl_Window
{
public:
	MainWindowPanel() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		begin();

		auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert};
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		{
			auto panel1 = new Panel(0, 0, 50, 0, "Test header 1", Docking::Left);
			{
				//panel->box(FL_UP_BOX);


				panel1->end();
			}

			auto panel2 = new Panel(0, 0, 0, 0, "Test header 2", Docking::Top);
			{
				//panel->box(FL_UP_BOX);


				panel2->end();
			}

			fl->end();
		}

		end();
	}
};

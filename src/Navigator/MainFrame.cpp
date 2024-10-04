#include <pch.h>
#include "MainFrame.h"
#include "Controls/Toolbars/Toolbar.h"

MainFrame::MainFrame()
	: Fl_Window(720, 648, "Navigator")
{
	using namespace FltkExt::Containers;

	auto centerflex = new Flex{ 0, 0, w(), h(), Direction::Vert };
	{
		centerflex->SetLayoutStrategy(LayoutStrategy::Full);

		auto toolbar = new Toolbar{ 0, 0, 40, 40 };
		{
			toolbar->box(FL_FREE_BOXTYPE);

			toolbar->end();
		}

		auto horzflex = new Flex{ 0, 0, 0, 0, Direction::Horz };
		{
			horzflex->box(FL_FREE_BOXTYPE);
			horzflex->SetLayoutStrategy(LayoutStrategy::Full);
			auto leftbar1 = new Flex{ 0, 0, 80, 80, Direction::Vert };
			{
				leftbar1->box(FL_FREE_BOXTYPE);
				leftbar1->margin(Margin{ 4 });


				leftbar1->end();
			}

			horzflex->end();
		}

		auto statusbar = new Flex{ 0, 0, 20, 20, Direction::Horz };
		{
			statusbar->box(FL_FREE_BOXTYPE);
			statusbar->gap(5);
			statusbar->margin(Margin(2));


			statusbar->end();
		}

		centerflex->end();
	}

}


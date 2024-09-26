#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Grid.h"


class MainWindowGrid : public Fl_Window
{
public:
	MainWindowGrid() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		CreateFlexAndGrid();
	}

private:
	void CreateFlexAndGrid()
	{
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Horz};
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		fl->margin(Margin(10));
		{
			auto gr = new Grid{ 0, 0, 0, 0, 3, 5 };
			gr->box(FL_FREE_BOXTYPE);

			fl->end();
		}

	}

};


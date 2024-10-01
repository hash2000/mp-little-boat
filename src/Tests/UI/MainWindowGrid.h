#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Grid.h"
#include <sstream>

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
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Horz };
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		fl->margin(Margin(10));
		{
			auto gr = new Grid{ 0, 0, 0, 0 };

			gr->AllowRowsIncrease(true);

			gr->AddRow(GridRow{ .height = 40, .gap = 5 });
			gr->AddRow(GridRow{ .height = 100, .gap = 10 });
			gr->AddRow(GridRow{ .height = 60, .gap = 0 });

			gr->AddColumn(GridColumn{ .width = 100, .gap = 5 });
			gr->AddColumn(GridColumn{ .width = 200, .gap = 0 });
			gr->AddColumn(GridColumn{ .width = 50, .gap = 0 });

			gr->box(FL_FREE_BOXTYPE);
			{
				char title[20];
				for (int i = 0; i < 10; i++)
				{
					std::sprintf(title, "bt%d", i);

					auto b1c1 = new Fl_Button{ 0, 0, 0, 0 };
					b1c1->copy_label(title);
					gr->AddWidget(b1c1, i, 0);

					auto b2c1 = new Fl_Button{ 0, 0, 0, 0 };
					b2c1->copy_label(title);
					gr->AddWidget(b2c1, i, 1);

					auto b3c1 = new Fl_Button{ 0, 0, 0, 0 };
					b3c1->copy_label(title);
					gr->AddWidget(b3c1, i, 2);
				}

				gr->end();
			}

			fl->end();
		}

	}

};


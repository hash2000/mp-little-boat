#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"


class MainWindowFlex : public Fl_Window
{
public:
	MainWindowFlex() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		auto centerfl = new Flex{ 0, 0, w(), h(), Direction::Vert };
		centerfl->docking(Docking::Full);
		centerfl->box(FL_FREE_BOXTYPE);
		{
			auto toolbar = new Flex{ 0, 0, 20, 20, Direction::Horz };
			{
				toolbar->box(FL_FREE_BOXTYPE);
				toolbar->spacing(5);
				toolbar->margin(Margin(2));

				CreateWidget(0, 0, 40, 40, FL_RED, "btn1");
				CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "btn2");
				CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");
				CreateWidget(0, 0, 0, 0, FL_DARK_RED, "btn4");

				toolbar->end();
			}

			auto horzContent = new Flex{ 0, 0, 0, 0, Direction::Horz };
			{
				horzContent->box(FL_FREE_BOXTYPE);
				horzContent->docking(Docking::Full);
				auto leftbar1 = new Flex{ 0, 0, 40, 40, Direction::Vert };
				{
					leftbar1->box(FL_FREE_BOXTYPE);
					leftbar1->margin(Margin{ 4 });
					CreateWidget(0, 0, 40, 40, FL_RED, "btn1");
					CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "btn2");
					CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");

					leftbar1->end();
				}

				auto leftbar2 = new Flex{ 0, 0, 40, 40, Direction::Vert };
				{
					leftbar2->box(FL_FREE_BOXTYPE);
					leftbar2->margin(Margin{ 4 });
					CreateWidget(0, 0, 40, 40, FL_RED, "btn1");
					CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "btn2");
					CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");

					leftbar2->end();
				}

				horzContent->end();
			}

			auto statusbar = new Flex{ 0, 0, 20, 20, Direction::Horz };
			{
				statusbar->box(FL_FREE_BOXTYPE);
				statusbar->spacing(5);
				statusbar->margin(Margin(2));

				CreateWidget(0, 0, 40, 40, FL_RED, "btn1");
				CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "btn2");
				CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");
				CreateWidget(0, 0, 0, 0, FL_DARK_RED, "btn4");

				statusbar->end();
			}

			centerfl->end();
		}
	}

	Fl_Widget* CreateWidget(int cx, int cy, int cw, int ch, Fl_Color color, const char* title)
	{
		auto result = new Fl_Box{ cx, cy, cw, ch, title };
		result->color(fl_color_average(color, FL_WHITE, 0.5));
		result->box(FL_FLAT_BOX);
		return result;
	}
};

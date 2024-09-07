#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"

class Toolbar : public Flex
{
public:
	Toolbar(int cx, int cy, int cw, int ch)
		: Flex(cx, cy, cw, ch,
			Flex::Direction::Horz,
			Flex::PushPosition::Start,
			Flex::Docking::ByDirection, 3)
	{
		box(FL_FREE_BOXTYPE);
		_f2b1.color(fl_color_average(FL_RED, FL_WHITE, 0.5));
		_f2b1.box(FL_FLAT_BOX);

		_f2b2.color(fl_color_average(FL_DARK_GREEN, FL_WHITE, 0.5));
		_f2b2.box(FL_FLAT_BOX);

		_f2b3.color(fl_color_average(FL_BLUE, FL_WHITE, 0.5));
		_f2b3.box(FL_FLAT_BOX);

		_f2b4.color(fl_color_average(FL_DARK_RED, FL_WHITE, 0.5));
		_f2b4.box(FL_FLAT_BOX);
	}

private:
	Fl_Box _f2b1{ 0, 0, 40, 40, "btn1" };
	Fl_Box _f2b2{ 0, 0, 0, 0, "btn2" };
	Fl_Box _f2b3{ 0, 0, 0, 0, "btn3" };
	Fl_Box _f2b4{ 0, 0, 0, 0, "btn4" };
	FlexEnd _flex2End;
};

class MainWindowFlex : public Fl_Window
{
public:
	MainWindowFlex() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		_flex.box(FL_FREE_BOXTYPE);
	}

private:
	Flex _flex{ 0, 0, w(), h(),
		Flex::Direction::Vert,
		Flex::PushPosition::Start,
		Flex::Docking::Full };
	Toolbar _toolbar1{ 0, 0, w(), 40 };
	Toolbar _toolbar2{ 0, 0, w(), 40 };
	FlexEnd _flex2End;
};

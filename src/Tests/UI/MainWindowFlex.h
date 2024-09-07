#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"

class Toolbar : public Flex
{
public:
	Toolbar(int cx, int cy, int cw, int ch, Direction dir)
		: Flex(cx, cy, cw, ch, dir, PushPosition::Start)
	{
		box(FL_FREE_BOXTYPE);
		spacing(5);
		margin(Margin(10, 6, 10, 4));

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
	ContainerEnd _flex2End;
};

class MainWindowFlex : public Fl_Window
{
public:
	MainWindowFlex() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		_flex.box(FL_FREE_BOXTYPE);
		_flex.docking(Docking::Full);
		_flex.margin(Margin(10));
		_flex.spacing(4);
	}

private:
	Flex _flex{ 0, 0, w(), h(), Direction::Vert, PushPosition::Start };
//	Toolbar _toolbar1{ 0, 0, w(), 40, Flex::Direction::Horz };
	Toolbar _toolbar2{ 0, 0, w(), 70, Direction::Horz };
	Toolbar _toolbar3{ 0, 80, 70, h() - 80, Direction::Vert };
	ContainerEnd _flex2End;
};

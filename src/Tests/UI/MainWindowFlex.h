#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"

class MainWindowFlex : public Fl_Window
{
public:
	MainWindowFlex() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		//_flex.box(FL_FREE_BOXTYPE);

		//_b1.color(fl_color_average(FL_RED, FL_WHITE, 0.5));
		//_b1.box(FL_FLAT_BOX);

		//_b2.color(fl_color_average(FL_DARK_GREEN, FL_WHITE, 0.5));
		//_b2.box(FL_FLAT_BOX);

		//_b3.color(fl_color_average(FL_BLUE, FL_WHITE, 0.5));
		//_b3.box(FL_FLAT_BOX);

		//_b4.color(fl_color_average(FL_YELLOW, FL_WHITE, 0.5));
		//_b4.box(FL_FLAT_BOX);

		//_b5.color(fl_color_average(FL_CYAN, FL_WHITE, 0.5));
		//_b5.box(FL_FLAT_BOX);

		//_b6.color(fl_color_average(FL_MAGENTA, FL_WHITE, 0.5));
		//_b6.box(FL_FLAT_BOX);

		//_b7.color(fl_color_average(FL_DARK_RED, FL_WHITE, 0.5));
		//_b7.box(FL_FLAT_BOX);

		_flex2.box(FL_FREE_BOXTYPE);
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
	Flex _flex2{ Flex::Horz, Flex::End, 40, 4 };
	Fl_Box _f2b1{ 0, 0, 40, 40, "btn1" };
	Fl_Box _f2b2{ 0, 0, 0, 0, "btn2" };
	Fl_Box _f2b3{ 0, 0, 0, 0, "btn3" };
	Fl_Box _f2b4{ 0, 0, 0, 0, "btn4" };

	//Flex _flex{ Flex::Horz, Flex::Start, 40, 4 };
	//Fl_Box _b1{ 0, 0, 0, 0, "btn1" };
	//Fl_Box _b2{ 0, 0, 0, 0, "btn2" };
	//Fl_Box _b3{ 0, 0, 0, 0, "btn3" };
	//Fl_Box _b4{ 0, 0, 0, 0, "btn4" };
	//Fl_Box _b5{ 0, 0, 0, 0, "btn5" };
	//Fl_Box _b6{ 0, 0, 0, 0, "btn6" };
	//Fl_Box _b7{ 0, 0, 0, 0, "btn7" };
	//FlexEnd _flexEnd;

	FlexEnd _flex2End;

};

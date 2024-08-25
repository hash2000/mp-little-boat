#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Adjuster.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Fill_Dial.H>
#include <FL/Fl_Line_Dial.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Hor_Nice_Slider.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Pack.H>

#include <map>
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include "Controls/Toolbars/ToolbarGlobalApps.h"

class MainFrame : public Fl_Window
{
public:
	MainFrame();

private:
	ToolbarGlobalApps _toolbarGlobalApps;
};

#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/TabbedPanel.h"
#include "Libs/FltkExt/Containers//Grid.h"
#include "Libs/FltkExt/Containers/Layout.h"
#include "Libs/FltkExt/Controls/DateTimePicker.h"

using namespace FltkExt::Containers;
using namespace FltkExt::Controls;
using namespace FltkExt::Data;

class MainWindowPickers : public Fl_Window
{
public:
	MainWindowPickers()
		: Fl_Window(800, 500, "Test FLTK UI")
	{
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Horz };
		fl->margin(Margin{ 10 });
		fl->gap(10);
		{
			auto dp = new DateTimePicker{0, 0, 200, 22};
			dp->SetDateTime(Poco::DateTime{ 2024, 10, 17, 18, 30, 57 });

			fl->end();
		}
	}
};

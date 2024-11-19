#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/TabbedPanel.h"
#include "Libs/FltkExt/Containers//Grid.h"
#include "Libs/FltkExt/Containers/Layout.h"
#include "Libs/FltkExt/Controls/DateTimePicker.h"
#include "Libs/FltkExt/Controls/Picker.h"
#include <chrono>

using namespace FltkExt::Containers;
using namespace FltkExt::Controls;
using namespace FltkExt::Data;

class MainWindowPickers : public Fl_Window
{
public:
	MainWindowPickers()
		: Fl_Window(800, 500, "Test FLTK UI")
	{
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		{

			auto fh = new Flex{ 0, 0, 40, 40, Direction::Horz };
			fh->margin(Margin{ 10 });
			fh->gap(10);
			{
				auto dp = new DateTimePicker{ 0, 0, 150, 22 };

				dp->SetDateTime(Poco::DateTime());

				auto mb = new Fl_Menu_Button{ 0, 0, 100, 22, "Menu btn" };
				mb->add("test1");
				mb->add("test2");
				mb->add("test3");
				mb->add("test4");

				auto btPicker = new Fl_Button(0, 0, 100, 22, "picker");
				btPicker->callback([](Fl_Widget* widget, void* data)
					{
						Fl_Button* thisBtn = (Fl_Button*)data;
						std::make_shared<Picker>(300, 320)->PoolDown(thisBtn);
						
					}, btPicker);

				fh->end();
			}

			fl->end();
		}
	}
};

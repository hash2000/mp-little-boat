#include "DateTimePicker.h"
#include "Resources/Icons.h"
#include <Poco/DateTimeFormatter.h>

namespace FltkExt::Controls
{
	using Flex = Containers::Flex;
	using Direction = Containers::Direction;
	using LayoutStrategy = Containers::LayoutStrategy;

	DateTimePicker::DateTimePicker(int cx, int cy, int cw, int ch)
		: Flex(cx, cy, cw, ch, Direction::Horz)
	{
		gap(1);

		_text = std::make_unique<Fl_Input>(0, 0, 0, 0);
		_text->readonly(1);
		_text->box(FL_THIN_DOWN_BOX);
		_picker = std::make_unique<Fl_Menu_Button>(0, 0, ch, ch);
		_picker->add("1", 0, [](Fl_Widget* sender, void* data) {
			auto me = (DateTimePicker*)data;
			}, this, 0);

		end();
	}

	void DateTimePicker::SetDateTime(const Poco::DateTime& date)
	{
		_date = date;
		ResetData();
	}

	void DateTimePicker::SetDateTimeMask(const std::string& mask)
	{
		_mask = mask;
		ResetData();
	}

	void DateTimePicker::ResetData()
	{
		_text->value(Poco::DateTimeFormatter::format(_date, _mask).c_str());
		redraw();
	}
}

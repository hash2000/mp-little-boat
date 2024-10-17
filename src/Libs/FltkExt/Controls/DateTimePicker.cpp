#include "DateTimePicker.h"
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


		_text = std::make_unique<Fl_Text_Buffer>();
		_edit = std::make_unique<Fl_Text_Display>(0, 0, 0, 0);
		_edit->box(FL_THIN_DOWN_BOX);
		_edit->buffer(_text.get());

		_picker = std::make_unique<Fl_Button>(0, 0, ch, ch);

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
		_text->text(Poco::DateTimeFormatter::format(_date, _mask).c_str());
		redraw();
	}
}

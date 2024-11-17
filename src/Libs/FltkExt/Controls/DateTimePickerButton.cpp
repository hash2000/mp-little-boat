#include "DateTimePickerButton.h"
#include "DateTimeSettings.h"

namespace FltkExt::Controls
{

	DateTimePickerButton::DateTimePickerButton(int cx, int cy, int cw, int ch)
		: Fl_Button(cx, cy, cw, ch)
	{
	}

	void DateTimePickerButton::SetDate(const Poco::DateTime& date, const Poco::DateTime& selectedMonthDate, const Poco::DateTime& selectedDate)
	{
		_date = date;

		auto weekList = WeekView::GetList();
		auto currentDayOfWeek = _date.dayOfWeek() - 1;
		currentDayOfWeek = currentDayOfWeek < 0 ? 6 : currentDayOfWeek;
		auto currentDay = _date.day();
		auto week = weekList[currentDayOfWeek];

		labelcolor(week->GetColor());
		copy_label(std::to_string(currentDay).c_str());

		if (selectedMonthDate.month() != _date.month()) {
			box(Settings::Buttons::ButtonBoxAnotherMonth);
			down_box(Settings::Buttons::ButtonDownBoxAnotherMonth);
		}
		else if (selectedDate == _date) {
			box(Settings::Buttons::ButtonBoxCurrentDate);
			down_box(Settings::Buttons::ButtonDownBoxCurrentDate);
		}
		else {
			box(Settings::Buttons::ButtonBox);
			down_box(Settings::Buttons::ButtonDownBoxDefault);
		}

		redraw();
	}

	Poco::DateTime DateTimePickerButton::GetDate() const
	{
		return _date;
	}

}

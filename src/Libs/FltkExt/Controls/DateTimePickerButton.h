#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <Poco/DateTime.h>
#include "Libs/FltkExt/Controls/DateTimeSettings.h"

namespace FltkExt::Controls
{
	class DateTimePickerButton : public Fl_Button
	{
	private:
		using WeekView = Settings::WeekView;

	public:
		DateTimePickerButton(int cx, int cy, int cw, int ch);

		void SetDate(const Poco::DateTime& date, const Poco::DateTime& selectedMonthDate, const Poco::DateTime& selectedDate);

		Poco::DateTime GetDate() const;

	private:
		Poco::DateTime _date;
	};

}

#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "Libs/FltkExt/Controls/Picker.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Margin.h"
#include "Libs/FltkExt/Controls/DateTimeSettings.h"
#include "Libs/FltkExt/Controls/DateTimePickerButton.h"
#include <memory>
#include <vector>
#include <Poco/DateTime.h>

namespace FltkExt::Controls
{
	class DateTimePickerView : public Picker
	{
	private:
		using Flex = Containers::Flex;
		using Direction = Containers::Direction;
		using LayoutStrategy = Containers::LayoutStrategy;
		using PushPosition = Containers::PushPosition;
		using Margin = Containers::Margin;
		using WeekView = Settings::WeekView;

	public:
		DateTimePickerView(const Poco::DateTime& date);

		Poco::DateTime GetDate() const;

	private:
		void ResetDates(const Poco::DateTime& date);

		Poco::Timespan GetMonthSpan() const;

		void SetDate(const Poco::DateTime& date);

		Poco::DateTime GetViewDate() const;

		void SetViewDate(const Poco::DateTime& date);

	private:
		std::unique_ptr<Flex> _mainFlex;
		std::unique_ptr<Flex> _headerFlex;
		std::unique_ptr<Fl_Button> _nextMonth;
		std::unique_ptr<Fl_Button> _prevMonth;
		std::unique_ptr<Fl_Box> _headerLabel;
		std::unique_ptr<Flex> _weeksFlex;
		std::vector<std::unique_ptr<Fl_Box>> _weeks;
		std::vector<std::unique_ptr<Flex>> _datesLines;
		std::vector<std::unique_ptr<DateTimePickerButton>> _dates;
		Poco::DateTime _date;
		Poco::DateTime _viewDate;
	};

}

#include "DateTimePickerView.h"
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>

namespace FltkExt::Controls
{
	DateTimePickerView::DateTimePickerView(const Poco::DateTime& date)
		: Picker(Settings::Views::ViewWidth, Settings::Views::ViewHeight)
		, _date(date)
		, _viewDate(date)
	{
		auto weekList = WeekView::GetList();

		_mainFlex = std::make_unique<Flex>(0, 0, w(), h(), Direction::Vert);
		_mainFlex->SetLayoutStrategy(LayoutStrategy::Full);
		_mainFlex->margin(Margin(Settings::Views::HeaderMargin));
		_mainFlex->gap(Settings::Views::BoxHeaderGap);
		{
			_headerFlex = std::make_unique<Flex>(Settings::Views::BoxSize, Direction::Horz, PushPosition::End);
			_headerFlex->gap(Settings::Views::BoxGap);
			{
				_nextMonth = std::make_unique<Fl_Button>(0, 0, Settings::Views::BoxSize, Settings::Views::BoxSize);
				_nextMonth->copy_label(">>");
				_nextMonth->box(Settings::Buttons::ButtonBox);
				_nextMonth->callback([](Fl_Widget* widget, void* data)
					{
						auto me = (Fl_Button*)widget;
						auto view = (DateTimePickerView*)data;
						auto selectedDate = view->GetViewDate();
						auto newdate = selectedDate + view->GetMonthSpan();
						view->SetViewDate(newdate);
						view->ResetDates(newdate);
					}, this);

				_prevMonth = std::make_unique<Fl_Button>(0, 0, Settings::Views::BoxSize, Settings::Views::BoxSize);
				_prevMonth->copy_label("<<");
				_prevMonth->box(Settings::Buttons::ButtonBox);
				_prevMonth->callback([](Fl_Widget* widget, void* data)
					{
						auto me = (Fl_Button*)widget;
						auto view = (DateTimePickerView*)data;
						auto selectedDate = view->GetViewDate();
						auto newdate = selectedDate - view->GetMonthSpan();
						view->SetViewDate(newdate);
						view->ResetDates(newdate);
					}, this);

				_headerLabel = std::make_unique<Fl_Box>(0, 0, 0, Settings::Views::BoxSize);
				_headerLabel->box(FL_FLAT_BOX);
				_headerLabel->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
				_headerLabel->labelcolor(fl_darker(FL_BLUE));

				_headerFlex->end();
			}

			_weeksFlex = std::make_unique<Flex>(Settings::Views::BoxSize, Direction::Horz);
			_weeksFlex->gap(Settings::Views::BoxGap);
			{
				_weeks.resize(weekList.size());
				for (int i = 0; i < weekList.size(); i++)
				{
					auto pWeek = weekList[i].get();
					auto week = std::make_unique<Fl_Box>(0, 0, Settings::Views::BoxSize, Settings::Views::BoxSize);
					week->copy_label(pWeek->GetName().c_str());
					week->labelcolor(pWeek->GetColor());

					_weeks[i] = std::move(week);
				}

				_weeksFlex->end();
			}

			_datesLines.resize(6);
			_dates.resize(_datesLines.size() * weekList.size());

			for (int line = 0; line < _datesLines.size(); line++)
			{
				auto lineFlex = std::make_unique<Flex>(Settings::Views::BoxSize, Direction::Horz);
				lineFlex->gap(Settings::Views::BoxGap);

				for (int weekid = 0; weekid < weekList.size(); weekid++)
				{
					auto dateid = line * weekList.size() + weekid;
					auto btnDate = std::make_unique<DateTimePickerButton>(0, 0, Settings::Views::BoxSize, Settings::Views::BoxSize);
					btnDate->callback([](Fl_Widget* widget, void* data)
						{
							auto me = (DateTimePickerButton*)widget;
							auto view = (DateTimePickerView*)data;
							view->SetDate(me->GetDate());
							view->OnOk();
						}, this);
					_dates[dateid] = std::move(btnDate);
				}

				lineFlex->end();
				_datesLines[line] = std::move(lineFlex);
			}

			_mainFlex->end();
		}

		ResetDates(_date);
	}

	void DateTimePickerView::ResetDates(const Poco::DateTime& date)
	{
		auto weekList = WeekView::GetList();
		auto firstDayOfMonth = Poco::DateTime{ date.year(), date.month(), 1 };
		auto firstDayOfMonthWeek = firstDayOfMonth.dayOfWeek() - 1;
		firstDayOfMonthWeek = firstDayOfMonthWeek < 0 ? 6 : firstDayOfMonthWeek;
		auto currentDayOfWeek = date.dayOfWeek() - 1;
		currentDayOfWeek = currentDayOfWeek < 0 ? 6 : currentDayOfWeek;
		auto currentDay = date.day();
		auto currentLine = (int((currentDay + firstDayOfMonthWeek - 1) / weekList.size()));
		auto currentDate = date;
		currentDate -= Poco::Timespan{ (int)(currentLine * weekList.size() + currentDayOfWeek), 0, 0, 0, 0 };

		for (int line = 0; line < _datesLines.size(); line++)
		{
			for (int weekid = 0; weekid < weekList.size(); weekid++)
			{
				auto dateid = line * weekList.size() + weekid;
				auto btnDate = _dates[dateid].get();
				btnDate->SetDate(currentDate, _viewDate, _date);
				currentDate += Poco::Timespan{ 1, 0, 0, 0, 0 };
			}
		}

		_headerLabel->copy_label(Poco::DateTimeFormatter::format(_viewDate, "%Y.%m").c_str());

		redraw();
	}

	Poco::Timespan DateTimePickerView::GetMonthSpan() const
	{
		return Poco::Timespan{ Poco::DateTime::daysOfMonth(_viewDate.year(), _viewDate.month()), 0, 0, 0, 0 };
	}

	void DateTimePickerView::SetDate(const Poco::DateTime& date)
	{
		_date = date;
	}

	Poco::DateTime DateTimePickerView::GetViewDate() const
	{
		return _viewDate;
	}

	void DateTimePickerView::SetViewDate(const Poco::DateTime& date)
	{
		_viewDate = date;
	}

	Poco::DateTime DateTimePickerView::GetDate() const
	{
		return _date;
	}


}


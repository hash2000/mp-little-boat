#include "DateTimePickerView.h"

namespace FltkExt::Controls
{
	namespace
	{
		static const int ViewWidth = 200;
		static const int ViewHeight = 225;
		static const int BoxSize = 25;
		static const int BoxHeaderGap = 2;
		static const int BoxGap = 2;
		static const int HeaderMargin = 5;
		static const Fl_Boxtype ButtonBoxDefault = FL_UP_BOX;
		static const Fl_Boxtype ButtonDownBoxDefault = FL_NO_BOX;
		static const Fl_Boxtype ButtonBox = FL_THIN_UP_FRAME;
		static const Fl_Boxtype ButtonBoxCurrentDate = FL_BORDER_BOX;
		static const Fl_Boxtype ButtonDownBoxCurrentDate = FL_DOWN_FRAME;
		static const Fl_Boxtype ButtonBoxAnotherMonth = FL_NO_BOX;
		static const Fl_Boxtype ButtonDownBoxAnotherMonth = FL_DOWN_FRAME;
	}

	DateTimePickerView::DateTimePickerView(const Poco::DateTime& date)
		: Picker(ViewWidth, ViewHeight)
		, _date(date)
	{
		auto weekList = WeekView::GetList();

		_mainFlex = std::make_unique<Flex>(0, 0, w(), h(), Direction::Vert);
		_mainFlex->SetLayoutStrategy(LayoutStrategy::Full);
		_mainFlex->margin(Margin(HeaderMargin));
		_mainFlex->gap(BoxHeaderGap);
		{
			_headerFlex = std::make_unique<Flex>(BoxSize, Direction::Horz, PushPosition::End);
			_headerFlex->gap(BoxGap);
			{
				_nextMonth = std::make_unique<Fl_Button>(0, 0, BoxSize, BoxSize);
				_nextMonth->copy_label(">>");
				_nextMonth->box(ButtonBox);

				_prevMonth = std::make_unique<Fl_Button>(0, 0, BoxSize, BoxSize);
				_prevMonth->copy_label("<<");
				_prevMonth->box(ButtonBox);

				_headerLabel = std::make_unique<Fl_Box>(0, 0, 0, BoxSize);
				_headerLabel->copy_label("2024 ноябрь");

				_headerFlex->end();
			}

			_weeksFlex = std::make_unique<Flex>(BoxSize, Direction::Horz);
			_weeksFlex->gap(BoxGap);
			{
				_weeks.resize(weekList.size());
				for (int i = 0 ; i < weekList.size(); i++)
				{
					auto pWeek = weekList[i].get();
					auto week = std::make_unique<Fl_Box>(0, 0, BoxSize, BoxSize);
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
				auto lineFlex = std::make_unique<Flex>(BoxSize, Direction::Horz);
				lineFlex->gap(BoxGap);

				for (int weekid = 0 ; weekid < weekList.size(); weekid++)
				{
					auto dateid = line * weekList.size() + weekid;
					auto btnDate = std::make_unique<Fl_Button>(0, 0, BoxSize, BoxSize);
					_dates[dateid] = std::move(btnDate);
				}

				lineFlex->end();
				_datesLines[line] = std::move(lineFlex);
			}

			_mainFlex->end();
		}

		ResetDates();
	}

	void DateTimePickerView::ResetDates()
	{
		auto weekList = WeekView::GetList();
		auto currentDayOfWeek = _date.dayOfWeek() - 1;
		currentDayOfWeek = currentDayOfWeek < 0 ? 6 : currentDayOfWeek;
		auto currentDay = _date.day();
		auto currentLine = (currentDay % weekList.size()) - 1;
		auto currentDate = _date;
		currentDate -= Poco::Timespan{ (int)(currentLine * weekList.size() + currentDayOfWeek), 0, 0, 0, 0 };

		for (int line = 0; line < _datesLines.size(); line++)
		{
			for (int weekid = 0; weekid < weekList.size(); weekid++)
			{
				auto week = weekList[weekid];
				auto dateid = line * weekList.size() + weekid;
				auto day = currentDate.day();
				auto month = currentDate.month();
				currentDate += Poco::Timespan{ 1, 0, 0, 0, 0 };

				auto btnDate = _dates[dateid].get();
				btnDate->labelcolor(week->GetColor());
				btnDate->copy_label(std::to_string(day).c_str());

				if (currentDate.month() != _date.month()) {
					btnDate->box(ButtonBoxAnotherMonth);
					btnDate->down_box(ButtonDownBoxAnotherMonth);
				}
				else if (currentDate == _date) {
					btnDate->box(ButtonBoxCurrentDate);
					btnDate->down_box(ButtonDownBoxCurrentDate);
				}
				else {
					btnDate->box(ButtonBox);
					btnDate->down_box(ButtonDownBoxDefault);
				}
			}
		}
	}


}


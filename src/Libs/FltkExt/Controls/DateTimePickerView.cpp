#include "DateTimePickerView.h"

namespace FltkExt::Controls
{
	namespace
	{
		static const int ViewSize = 170;
		static const int BoxSize = 20;
		static const int BoxHeaderGap = 2;
		static const int BoxGap = 2;
		static const int HeaderMargin = 5;
		static const Fl_Boxtype ButtonBox = FL_THIN_UP_FRAME;
	}

	DateTimePickerView::DateTimePickerView(const Poco::DateTime& date)
		: Picker(ViewSize, ViewSize)
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

			_datesLines.resize(7);
			_dates.resize(_datesLines.size() * weekList.size());


			for (int line = 0; line < _datesLines.size(); line++)
			{
				auto lineFlex = std::make_unique<Flex>(BoxSize, Direction::Horz);
				lineFlex->gap(BoxGap);

				for (int weekid = 0 ; weekid < 7; weekid++)
				{
					auto week = weekList[weekid];
				}

				lineFlex->end();
				_datesLines[line] = std::move(lineFlex);
			}

			_mainFlex->end();
		}
	}


}


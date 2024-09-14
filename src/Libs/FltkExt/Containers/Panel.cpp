#include "Panel.h"
#include "Flex.h"
#include "Splitter.h"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

Panel::Panel(int size, const char* l)
	: Container(0, 0, size, size)
{
	//SetLayoutStrategy(LayoutStrategy::Full);

	auto headerColor = fl_lighter(FL_BLUE);
	auto headerTextColor = fl_lighter(FL_WHITE);
	auto headerSize = 30;

	_topFlex = std::make_unique<Flex>(0, 0, w(), h(), Direction::Vert);
	_topFlex->box(FL_FREE_BOXTYPE);
	_topFlex->SetLayoutStrategy(LayoutStrategy::Full);
	{
		_topContentFlex = std::make_unique<Flex>(0, 0, 0, 0, Direction::Vert);
		_topContentFlex->SetLayoutStrategy(LayoutStrategy::Full);
		_topContentFlex->margin(Margin(1));
		{
			_topHeaderFlex = std::make_unique<Flex>(0, 0, w(), headerSize, Direction::Horz, PushPosition::End);
			_topHeaderFlex->box(FL_FLAT_BOX);
			_topHeaderFlex->color(headerColor);
			_topHeaderFlex->label(l);
			_topHeaderFlex->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
			_topHeaderFlex->labelcolor(headerTextColor);
			{
				auto minimizeButton = new Fl_Button{ 0, 0, headerSize, headerSize };
				minimizeButton->color(headerColor);
				minimizeButton->box(FL_FLAT_BOX);

				_topHeaderFlex->end();
			}

			_topContentFlex->end();
		}

		_splitter = std::make_unique<Splitter>( 0, 0, 15, 15, Direction::Vert );
		_splitter->box(FL_FREE_BOXTYPE);
		_splitter->resizable(this);


		_topFlex->end();
	}
}

void Panel::UpdateDockingState(Docking docking)
{
	_docking = docking;
	auto direction = docking == Docking::Left || docking == Docking::Right ?
		Direction::Horz : Direction::Vert;
	_topFlex->direction(direction);
	_splitter->direction(direction);
}

Docking Panel::GetDockingState() const
{
	return _docking;
}

#include "Panel.h"
#include "Flex.h"
#include "Splitter.h"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

Panel::Panel(int cx, int cy, int cw, int ch, const char* l, Docking docking)
	: Flex(cx, cy, cw, ch, Direction::Vert)
{
	SetLayoutStrategy(LayoutStrategy::Full);

	auto headerColor = fl_lighter(FL_BLUE);
	auto headerTextColor = fl_lighter(FL_WHITE);
	auto headerSize = 30;
	auto topFlexDirection = docking == Docking::Left || docking == Docking::Right ?
		Direction::Horz : Direction::Vert;

	auto topFlex = new Flex{ 0, 0, 0, 0, topFlexDirection };
	topFlex->SetLayoutStrategy(LayoutStrategy::Full);
	topFlex->box(FL_FREE_BOXTYPE);
	{
		auto vert = new Flex{ 0, 0, 0, 0, Direction::Vert };
		vert->SetLayoutStrategy(LayoutStrategy::Full);
		vert->margin(Margin(1));
		{
			auto header = new Flex{ 0, 0, w(), headerSize, Direction::Horz, PushPosition::End };
			header->box(FL_FLAT_BOX);
			header->color(headerColor);
			header->label(l);
			header->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
			header->labelcolor(headerTextColor);
			{
				auto minimizeButton = new Fl_Button{ 0, 0, headerSize, headerSize };
				minimizeButton->color(headerColor);
				minimizeButton->box(FL_FLAT_BOX);

				header->end();
			}
			vert->end();
		}

		auto splitter = new Splitter{ 0, 0, 15, 15, topFlexDirection };
		splitter->box(FL_FREE_BOXTYPE);
		splitter->resizable(this);

		topFlex->end();
	}
}

void Panel::resize(int cx, int cy, int cw, int ch)
{
	_size = _direction == Direction::Horz ? ch: cw;
	Flex::resize(cx, cy, cw, ch);
}

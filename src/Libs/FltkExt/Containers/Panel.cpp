#include "Panel.h"
#include "Flex.h"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>

Panel::Panel(int cx, int cy, int cw, int ch, Docking docking)
	: Container(cx, cy, cw, ch, Direction::Vert)
{
	auto vert = new Flex{ 0, 0, w(), h(), Direction::Vert };
	vert->SetLayoutStrategy(LayoutStrategy::Full);
	vert->margin(Margin(1));
	{
		auto header = new Flex{ 0, 0, w(), 30, Direction::Horz, PushPosition::End };
		header->box(FL_FLAT_BOX);
		header->color(fl_lighter(FL_BLUE));
		header->margin(Margin(1));
		header->label("Test header label");
		header->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
		header->labelcolor(fl_lighter(FL_WHITE));
		{
			auto title = new Fl_Box{ 0, 0, 30, 30 };
			title->color(fl_lighter(FL_RED));
			title->box(FL_FLAT_BOX);

			header->end();
		}
		vert->end();
	}
}

void Panel::draw()
{
	int cx = x();
	int cy = y();
	int cw = w();
	int ch = h();

	draw_box(FL_UP_BOX, cx, cy, cw, ch, selection_color());



	Container::draw();
}

void Panel::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::BeginLayout(cx, cy, cw, ch);



	Container::EndLayout();
}

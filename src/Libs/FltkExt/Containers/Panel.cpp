#include "Panel.h"

Panel::Panel(int cx, int cy, int cw, int ch, Docking docking)
	: Container(cx, cy, cw, ch, Direction::Vert)
{
}

void Panel::draw()
{
	Container::draw();

	int cx = x();
	int cy = y();
	int cw = w();
	int ch = h();

	draw_box(FL_UP_BOX, cx, cy, cw, ch, selection_color());
}

void Panel::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::BeginLayout(cx, cy, cw, ch);



	Container::EndLayout();
}

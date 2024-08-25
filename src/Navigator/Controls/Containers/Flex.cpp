#include <pch.h>
#include "Flex.h"

Flex::Flex(Direction direction, Position pos, int size, const Margin& margin)
	: Fl_Group(0, 0, size, size, nullptr)
	, _direction(direction)
	, _position(pos)
	, _margin(margin)
	, _size(size)
{

	begin();
}

void Flex::AdjustLayout()
{
	const int nc = children();

	int dx = Fl::box_dx(box());
	int dy = Fl::box_dy(box());
	int dw = Fl::box_dw(box());
	int dh = Fl::box_dh(box());

	// Calculate total space minus gaps
	int gaps = nc > 1 ? nc - 1 : 0;
	int hori = _direction == Direction::Horz;
	int space = hori
		? (w() - dw - _margin._left - _margin._right)
		: (h() - dh - _margin._top - _margin._bottom);

	int xp = x() + dx + _margin._left;
	int yp = y() + dy + _margin._top;
	int hh = h() - dh - _margin._top - _margin._bottom; // if horizontal: constant height of widgets
	int vw = w() - dw - _margin._left - _margin._right; // if vertical:   constant width of widgets

	int fw = nc;

	for (int i = 0; i < nc; i++) {
		Fl_Widget* c = child(i);
		if (c->visible()) {
			space -= (hori ? c->w() : c->h());
			fw--;
		}
		else { // hidden widget
			fw--;
			gaps--;
		}
	}
}

void Flex::resize(int cx, int cy, int cw, int ch)
{
	Fl_Widget::resize(cx, cy, cw, ch);
	AdjustLayout();
}

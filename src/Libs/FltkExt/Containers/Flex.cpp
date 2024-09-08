#include "Flex.h"
#include <FL/Fl_Widget.H>
#include <algorithm>

Flex::Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position)
	: Container(cx, cy, cw, ch, direction, position)
	, _spacing(0)
{
	_size = _direction == Direction::Horz ? ch : cw;
	begin();
}

int Flex::spacing() const
{
	return _spacing;
}

void Flex::spacing(int size)
{
	_spacing = size;
}

void Flex::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::BeginLayout(cx, cy, cw, ch);

	const int nc = children();
	int fcount = 0;
	int fspace = 0;

	// Calculate inner control fixed sizes space
	for (int i = 0; i < nc; i++)
	{
		Fl_Widget* c = child(i);
		int sz = _direction == Direction::Horz ? _elements[i]->width : _elements[i]->height;
		if (sz > 0) {
			fspace += sz;
			fcount++;
		}
	}

	cx += _margin.left;
	cy += _margin.top;
	cw -= _margin.left + _margin.right;
	ch -= _margin.top + _margin.bottom;

	auto fixedSize = _size - (_direction == Direction::Horz ?
		_margin.top + _margin.bottom : _margin.left + _margin.right);

	auto ncsize = nc > 1 ? (nc - 1) * _spacing : 0;
	auto cstart = _direction == Direction::Horz ? cx : cy;
	auto csize = _direction == Direction::Horz ? cw : ch;

	auto nfcount = nc - fcount;
	auto ctlsize = 0;

	if (nfcount > 0) {
		ctlsize = csize - fspace - ncsize;
		ctlsize /= nfcount;
	}

	auto directionSize = _direction == Direction::Horz ? ch  : cw;
	auto dockingSize = _layoutStraategy == LayoutStrategy::ByDirection ? fixedSize : directionSize;

	for (int i = 0; i < nc; i++)
	{
		auto item = _position == PushPosition::Start ? i : nc - i - 1;
		Fl_Widget* c = child(item);

		auto size = _direction == Direction::Horz ? _elements[item]->width : _elements[item]->height;
		size = size == 0 ? ctlsize : size;

		auto px = _direction == Direction::Horz ? cstart : cx;
		auto py = _direction == Direction::Horz ? cy : cstart;
		auto pw = _direction == Direction::Horz ? size : dockingSize;
		auto ph = _direction == Direction::Horz ? dockingSize : size;

		c->resize(px, py, pw, ph);
		size = _direction == Direction::Horz ? c->w() : c->h();

		cstart += size + _spacing;
	}

	Container::EndLayout();
}


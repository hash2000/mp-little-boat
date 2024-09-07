#include "Flex.h"
#include <FL/Fl_Widget.H>
#include <algorithm>

Flex::Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position, Docking docking, int spacing)
	: Fl_Group(cx, cy, cw, ch, nullptr)
	, _direction(direction)
	, _position(position)
	, _docking(docking)
	, _spacing(spacing)
{
	_size = _direction == Direction::Horz ? ch : cw;
	begin();
}

void Flex::InitElementsContext()
{
	const int nc = children();

	if (_elements.size() != nc)
	{
		_elements.resize(nc);
		for (int i = 0; i < nc; i++)
		{
			Fl_Widget* c = child(i);
			_elements[i] = std::make_shared<ElementContext>();
			_elements[i]->width = c->w();
			_elements[i]->height = c->h();
		}
	}
}

void Flex::AdjustMainSizes(int cx, int cy, int cw, int ch)
{
	if (_docking == Docking::ByDirection)
	{
		if (_direction == Direction::Horz)
		{
			Fl_Group::resize(cx, cy, cw - cx, _size);
		}
		else
		{
			Fl_Group::resize(cx, cy, _size, ch - cy);
		}
	}
	else if (_docking == Docking::Full)
	{
		Fl_Group::resize(cx, cy, cw - cx, ch - cy);
	}
}

void Flex::AdjustLayout(int cx, int cy, int cw, int ch)
{
	InitElementsContext();
	AdjustMainSizes(cx, cy, cw, ch);

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

	auto ncsize = nc * _spacing;
	auto cstart = (_direction == Direction::Horz ? x() : y()) + _spacing;
	auto cend = (_direction == Direction::Horz ? w() : h());

	auto nfcount = nc - fcount;
	auto ctlsize = 0;

	if (nfcount > 0) {
		ctlsize = (cend - cstart - fspace - ncsize) / nfcount;
	}

	for (int i = 0; i < nc; i++)
	{
		auto item = _position == PushPosition::Start ? i : nc - i - 1;
		Fl_Widget* c = child(item);

		auto size = _direction == Direction::Horz ? _elements[item]->width : _elements[item]->height;
		size = size == 0 ? ctlsize : size;

		auto directionSize = _direction == Direction::Horz ? ch - cy : cw - cx;
		auto dockingSize = _docking == Docking::ByDirection ? _size - _spacing * 2 : directionSize;
		auto px = _direction == Direction::Horz ? cstart : cx + _spacing;
		auto py = _direction == Direction::Horz ? cy + _spacing : cstart;
		auto pw = _direction == Direction::Horz ? size : dockingSize;
		auto ph = _direction == Direction::Horz ? dockingSize : size;

		c->resize(px, py, pw, ph);
		size = _direction == Direction::Horz ? c->w() : c->h();

		cstart += size + _spacing;
	}

	_needRecalculate = false;
	redraw();
}

void Flex::RecalcLayout(bool set)
{
	_needRecalculate = set;
}

void Flex::resize(int cx, int cy, int cw, int ch)
{
	AdjustLayout(cx, cy, cw, ch);
}

void Flex::draw()
{
	if (_needRecalculate) {
		AdjustLayout(x(), y(), w(), h());
	}

	Fl_Group::draw();
}

void Flex::end()
{
	Fl_Group::end();
	RecalcLayout();
}

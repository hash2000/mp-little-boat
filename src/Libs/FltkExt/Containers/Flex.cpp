#include "Flex.h"
#include <FL/Fl_Widget.H>
#include <algorithm>

Flex::Flex(int direction, int pos, int size, int spacing)
	: Fl_Group(0, 0, 1, 1, nullptr)
	, _direction(direction)
	, _position(pos)
	, _size(size)
	, _spacing(spacing)
{
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
	if (_direction == Horz)
	{
		Fl_Group::resize(cx, cy, cw - cx, _size);
	}
	else
	{
		Fl_Group::resize(cx, cy, _size, ch - cy);
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
		int sz = _direction == Horz ? _elements[i]->width : _elements[i]->height;
		if (sz > 0) {
			fspace += sz;
			fcount++;
		}
	}

	auto ncsize = nc * _spacing;
	auto cstart = (_direction == Horz ? x() : y()) + _spacing;
	auto cend = (_direction == Horz ? w() : h());

	auto nfcount = nc - fcount;
	auto ctlsize = 0;

	if (nfcount > 0) {
		ctlsize = (cend - cstart - fspace - ncsize) / nfcount;
	}

	for (int i = 0; i < nc; i++)
	{
		auto item = _position == Start ? i : nc - i - 1;
		Fl_Widget* c = child(item);

		auto size = _direction == Horz ? _elements[item]->width : _elements[item]->height;
		size = size == 0 ? ctlsize : size;
		auto px = _direction == Horz ? cstart : cx + _spacing;
		auto py = _direction == Horz ? cy + _spacing : cstart;
		auto pw = _direction == Horz ? size : _size - _spacing * 2;
		auto ph = _direction == Horz ? _size - _spacing * 2: size;

		c->resize(px, py, pw, ph);
		size = _direction == Horz ? c->w() : c->h();

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
		auto pnt = parent();
		AdjustLayout(x(), y(), pnt->w(), pnt->h());
	}

	Fl_Group::draw();
}

void Flex::end()
{
	Fl_Group::end();
	RecalcLayout();
}

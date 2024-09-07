#include "Container.h"


Container::Container(int cx, int cy, int cw, int ch, Direction direction, PushPosition position)
	: Fl_Group(cx, cy, cw, ch, nullptr)
	, _direction(direction)
	, _position(position)
	, _docking(Docking::ByDirection)
{
	_size = _direction == Direction::Horz ? ch : cw;
	begin();
}

Docking Container::docking() const
{
	return _docking;
}

void Container::docking(Docking dock)
{
	_docking = dock;
}

Margin Container::margin() const
{
	return _margin;
}

void  Container::margin(const Margin& m)
{
	_margin = m;
}

void Container::RecalcLayout(bool set)
{
	_needRecalculate = set;
}

void Container::resize(int cx, int cy, int cw, int ch)
{
	AdjustLayout(cx, cy, cw, ch);
}

void Container::draw()
{
	if (_needRecalculate) {
		AdjustLayout(x(), y(), w() - x(), h() - y());
	}

	Fl_Group::draw();
}

void Container::end()
{
	Fl_Group::end();
	RecalcLayout();
}

void Container::BeginLayout(int cx, int cy, int cw, int ch)
{
	InitElementsContext();
	AdjustMainSizes(cx, cy, cw, ch);
}

void Container::EndLayout()
{
	_needRecalculate = false;
	redraw();
}

void Container::InitElementsContext()
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

void Container::AdjustMainSizes(int cx, int cy, int cw, int ch)
{
	if (_docking == Docking::ByDirection)
	{
		if (_direction == Direction::Horz)
		{
			Fl_Group::resize(cx, cy, cw, _size);
		}
		else
		{
			Fl_Group::resize(cx, cy, _size, ch);
		}
	}
	else if (_docking == Docking::Full)
	{
		Fl_Group::resize(cx, cy, cw, ch);
	}
}

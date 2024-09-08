#include "Container.h"


Container::Container(int cx, int cy, int cw, int ch, Direction direction, PushPosition position)
	: Fl_Group(cx, cy, cw, ch, nullptr)
	, _direction(direction)
	, _position(position)
	, _layoutStraategy(LayoutStrategy::ByDirection)
{
	_size = _direction == Direction::Horz ? ch : cw;
	begin();
}

PushPosition Container::GetPushPosition() const
{
	return _position;
}

void Container::SetPushPosition(PushPosition pos)
{
	_position = pos;
	RecalcLayout();
}

Direction Container::direction() const
{
	return _direction;
}

void Container::direction(Direction dir)
{
	_direction = dir;
	RecalcLayout();
}

LayoutStrategy Container::GetLayoutStrategy() const
{
	return _layoutStraategy;
}

void Container::SetLayoutStrategy(LayoutStrategy set)
{
	_layoutStraategy = set;
	RecalcLayout();
}

const Margin& Container::margin() const
{
	return _margin;
}

void  Container::margin(const Margin& m)
{
	_margin = m;
	RecalcLayout();
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
	if (_layoutStraategy == LayoutStrategy::ByDirection)
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
	else if (_layoutStraategy == LayoutStrategy::ByDirectionReflected)
	{
		if (_direction == Direction::Horz)
		{
			Fl_Group::resize(cx, parent()->h() - _size, cw, _size);
		}
		else
		{
			Fl_Group::resize(parent()->w() - _size, cy, _size, ch);
		}
	}
	else if (_layoutStraategy == LayoutStrategy::Full)
	{
		Fl_Group::resize(cx, cy, cw, ch);
	}
}

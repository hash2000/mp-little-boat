#include "Splitter.h"
#include <FL/fl_draw.H>

Splitter::Splitter(int cx, int cy, int cw, int ch, Direction direction)
	: Fl_Box(cx, cy, cw, ch)
	, _resizable(nullptr)
	, _resize_start(-1)
	, _direction(direction)
{
}

Direction Splitter::direction() const
{
	return _direction;
}

void Splitter::direction(Direction dir)
{
	_direction = dir;
}

PushPosition Splitter::GetPushPosition() const
{
	return _pushPosition;
}

void Splitter::SetPushPosition(PushPosition pos)
{
	_pushPosition = pos;
}


void Splitter::resizable(Fl_Widget* widget)
{
	_resizable = widget;
}

void Splitter::resizable(Fl_Widget& widget)
{
	_resizable = &widget;
}

Fl_Widget* Splitter::resizable() const
{
	return _resizable;
}

#include <iostream>

int Splitter::handle(int event)
{
	if (!_resizable) {
		return 0;
	}

	auto event_button = Fl::event_button();
	auto event_clicks = Fl::event_clicks();
	auto event_x = Fl::event_x();
	auto event_y = Fl::event_y();
	auto event_key = Fl::event_key();
	auto event_state = Fl::event_state();
	auto focus = Fl::focus();
	auto result = Fl_Widget::handle(event);
	auto rx = _resizable->x();
	auto ry = _resizable->y();
	auto rw = _resizable->w();
	auto rh = _resizable->h();
	auto minPanelSize = _direction == Direction::Vert ?
		h() + Fl::box_dx(box()) : w() + Fl::box_dx(box());
	minPanelSize += 15;

	switch (event)
	{
	case FL_PUSH:
		if (Fl::visible_focus())
		{
			if (event_button == 1 && !event_clicks)
			{
				if (focus == this) {
					take_focus();
					Fl_Widget::do_callback();
					result = 1;
				}

				_resize_start = _direction == Direction::Horz ? event_x : event_y;
				result = 1;
			}
		}
		break;
	case FL_DRAG:
		if (_resize_start != -1)
		{
			if (_direction == Direction::Horz)
			{
				auto offset = _resize_start - event_x;
				_resize_start = event_x;

				if (_pushPosition == PushPosition::Start) {
					if (rw - offset < minPanelSize) {
						offset = 0;
					}
					_resizable->resize(rx, ry, rw - offset, rh);
				}
				else {
					if (rw + offset < minPanelSize) {
						offset = 0;
					}
					_resizable->resize(rx - offset, ry, rw + offset, rh);
				}

				ChangeCursor(FL_CURSOR_WE);
			}
			else
			{
				auto offset = _resize_start - event_y;
				_resize_start = event_y;

				if (_pushPosition == PushPosition::Start) {
					if (rh - offset < minPanelSize) {
						offset = 0;
					}
					_resizable->resize(rx, ry, rw, rh - offset);
				}
				else {
					if (rh + offset < minPanelSize) {
						offset = 0;
					}
					_resizable->resize(rx, ry - offset, rw, rh + offset);
				}

				ChangeCursor(FL_CURSOR_NS);
			}

			auto p = _resizable->parent();
			if (p) {
				_resizable->parent()->resize(p->x(), p->y(), p->w(), p->h());
			}
		}
		break;
	case FL_RELEASE:
		if (event_button == 1)
		{
			ChangeCursor(FL_CURSOR_DEFAULT);
			result = 1;
		}
		break;
	case FL_FOCUS:
		Fl::focus(this);
	case FL_UNFOCUS:
		//_stop_auto_drag();
		result = 1;
		break;
	}

	return result;
}

void Splitter::ChangeCursor(Fl_Cursor newcursor)
{
	if (_lastCursor != newcursor) {
		_lastCursor = newcursor;
		fl_cursor(newcursor, FL_BLACK, FL_WHITE);
	}
}

bool Splitter::IsEventInside() const
{
	return Fl::event_inside(
		x() + Fl::box_dx(box()),
		y() + Fl::box_dy(box()),
		w() - Fl::box_dw(box()),
		h() - Fl::box_dh(box()));
}

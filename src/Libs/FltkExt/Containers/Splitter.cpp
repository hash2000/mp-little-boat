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

			//if (Fl_Widget::callback()) {
			//	Fl_Widget::do_callback();
			//}
		}
		break;
	case FL_DRAG:
		if (_resize_start != -1)
		{
			if (_direction == Direction::Horz)
			{
				auto offset = _resize_start - event_x;
				_resize_start = event_x;
				_resizable->resize(rx, ry, rw - offset, rh);
				ChangeCursor(FL_CURSOR_WE);
			}
			else
			{
				auto offset = _resize_start - event_y;
				_resize_start = event_y;
				_resizable->resize(rx, ry, rw, rh - offset);
				ChangeCursor(FL_CURSOR_NS);
			}

			DoRedrawAll();

			//if (Fl_Widget::callback() && (when() & FL_WHEN_CHANGED)) {
			//	Fl_Widget::callback();
			//}
		}
		break;
	case FL_RELEASE:
		//if (_resize_start == -1 && Fl_Widget::callback() && when() & FL_WHEN_RELEASE) {
		//	Fl_Widget::do_callback();
		//}

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

void Splitter::DoRedrawAll()
{
	redraw();
	if (_resizable != nullptr &&
		_resizable->parent() != nullptr) {
		_resizable->parent()->redraw();
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

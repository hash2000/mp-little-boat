#include "Splitter.h"
#include "Panel.h"
#include <FL/fl_draw.H>

namespace FltkExt::Containers
{


	Splitter::Splitter(int size, Direction direction)
		: Fl_Box(0, 0, size, size)
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
		if (auto panel = dynamic_cast<Panel*>(_resizable)) {
			minPanelSize += panel->GetMinPanelSize();
		}

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
					}

					_resizeStart = _direction == Direction::Horz ? event_x : event_y;
					result = 1;
				}
			}
			break;
		case FL_DRAG:
			if (_resizeStart != -1)
			{
				if (_direction == Direction::Horz)
				{
					auto offset = _resizeStart - event_x;
					_resizeStart = event_x;

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
				}
				else
				{
					auto offset = _resizeStart - event_y;
					_resizeStart = event_y;

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
				}

				auto p = _resizable->parent();
				if (p) {
					p->resize(p->x(), p->y(), p->w(), p->h());
					p->redraw();
				}

			}
			break;
		case FL_ENTER:
			if (_direction == Direction::Horz) {
				ChangeCursor(FL_CURSOR_WE);
			}
			else {
				ChangeCursor(FL_CURSOR_NS);
			}
			result = 1;
			break;
		case FL_LEAVE:
			ChangeCursor(FL_CURSOR_DEFAULT);
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


}

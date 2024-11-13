#include "Picker.h"
#include <iostream>

namespace FltkExt::Controls
{
	Picker::Picker()
		: Fl_Menu_Window(0, 0, 0, 0, nullptr)
	{
		set_modal();
		clear_border();
		set_menu_window();
		box(FL_UP_BOX);
	}

	Picker::~Picker()
	{
	}

	PickerResult Picker::PoolDown(Fl_Widget* owner, int cw, int ch)
	{
		if (!owner) {
			return PickerResult::OnCancel;
		}

		EndPicker();

		Fl_Group::current(0);
		Fl_Widget_Tracker wp(owner);

		int cx = owner->x();
		int cy = owner->y() + owner->h();

		if (owner && owner->window())
		{
			for (auto w = owner->window(); w; w = w->window()) {
				cx += w->x();
				cy += w->y();
			}
		}
		else
		{
			cx += Fl::event_x_root() - Fl::event_x();
			cy += Fl::event_y_root() - Fl::event_y();
		}

		resize(cx, cy, cw, ch);
		Fl::grab(this);

		while (true)
		{
			if (!shown()) {
				show();
			}

			Fl::wait();

			if (owner && wp.deleted()) {
				_result = PickerResult::OnCancel;
				break;
			}

			if (_result != PickerResult::Initialized) {
				break;
			}
		}

		EndPicker();
		return _result;
	}

	bool Picker::IsEventInside()
	{
		int cx = Fl::event_x();
		int cy = Fl::event_y();
		if (cx < 0 || cx >= w() ||
			cy < 0 || cy >= h()) {
			return false;
		}

		return true;
	}

	int Picker::handle(int event)
	{
		int cx = Fl::event_x();
		int cy = Fl::event_y();

		switch (event)
		{
		case FL_RELEASE:
			if (!IsEventInside()) {
				_result = PickerResult::OnCancel;
				return 1;
			}
		}

		return Fl_Menu_Window::handle(event);
	}

	void Picker::EndPicker()
	{
		_result = PickerResult::Initialized;

		if (shown()) {
			hide();
		}

		Fl::grab(nullptr);
	}

	void Picker::SetPickerResult(PickerResult result)
	{
		_result = result;
		redraw();
	}

}

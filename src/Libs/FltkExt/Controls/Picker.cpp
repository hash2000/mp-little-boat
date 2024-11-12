#include "Picker.h"

namespace FltkExt::Controls
{
	Picker::Picker()
		: Fl_Menu_Window(0, 0, 0, 0, nullptr)
	{
		end();
		set_modal();
		clear_border();
		set_menu_window();
		box(FL_UP_BOX);
	}

	Picker* Picker::GetInstance()
	{
		static Picker* _instance;
		if (!_instance) {
			_instance = new Picker();
		}
		return _instance;
	}

	PickerResult Picker::Do(Fl_Widget* owner, int cx, int cy)
	{
		if (!owner) {
			return PickerResult::OnCancel;
		}

		EndPicker();

		Fl_Group::current(0);
		Fl_Widget_Tracker wp(owner);

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

		resize(cx, cy, owner->w(), owner->h());
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

	int Picker::handle(int event)
	{
		switch (event)
		{
		case FL_RELEASE:
			_result = PickerResult::OnCancel;
			return 1;
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

}

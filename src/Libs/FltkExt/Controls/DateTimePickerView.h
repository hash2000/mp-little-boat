#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Window.H>
#include <memory>
#include "Picker.h"

namespace FltkExt::Controls
{
	class DateTimePickerView : public Picker
	{
	public:
		DateTimePickerView();
	};

}

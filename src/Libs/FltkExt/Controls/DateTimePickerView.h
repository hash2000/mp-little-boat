#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Window.H>
#include <memory>
#include "Libs/FltkExt/Controls/Picker.h"
#include "Libs/FltkExt/Containers/Flex.h"

namespace FltkExt::Controls
{
	class DateTimePickerView : public Picker
	{
	private:
		using Flex = Containers::Flex;
		using Direction = Containers::Direction;
		using LayoutStrategy = Containers::LayoutStrategy;

	public:
		DateTimePickerView(int cw, int ch);

	private:
		std::shared_ptr<Flex> _mainFlex;
	};

}

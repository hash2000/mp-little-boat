#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <Poco/DateTime.h>
#include "Libs/FltkExt/Containers/Flex.h"
#include <memory>
#include <string>

namespace FltkExt::Controls
{
	class DateTimePicker : public Containers::Flex
	{
	public:
		DateTimePicker(int cx, int cy, int cw, int ch);

		void SetDateTime(const Poco::DateTime& date);

		void SetDateTimeMask(const std::string& mask);

	protected:

		void ResetData();

	public:
		Poco::DateTime _date;
		std::string _mask = "%Y.%m.%d";
		std::unique_ptr<Fl_Input> _text;
		std::unique_ptr<Fl_Menu_Button> _picker;
	};
}


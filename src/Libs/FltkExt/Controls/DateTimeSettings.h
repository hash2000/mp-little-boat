#pragma once
#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>

namespace FltkExt::Controls::Settings
{
	namespace Views
	{
		static constexpr int ViewWidth = 200;
		static constexpr int ViewHeight = 225;
		static constexpr int BoxSize = 25;
		static constexpr int BoxHeaderGap = 2;
		static constexpr int BoxGap = 2;
		static constexpr int HeaderMargin = 5;
	}

	namespace Buttons
	{
		static constexpr Fl_Boxtype ButtonBoxDefault = FL_UP_BOX;
		static constexpr Fl_Boxtype ButtonDownBoxDefault = FL_NO_BOX;
		static constexpr Fl_Boxtype ButtonBox = FL_THIN_UP_FRAME;
		static constexpr Fl_Boxtype ButtonBoxCurrentDate = FL_BORDER_BOX;
		static constexpr Fl_Boxtype ButtonDownBoxCurrentDate = FL_DOWN_FRAME;
		static constexpr Fl_Boxtype ButtonBoxAnotherMonth = FL_NO_BOX;
		static constexpr Fl_Boxtype ButtonDownBoxAnotherMonth = FL_DOWN_FRAME;
	}

	class WeekView
	{
	private:
		struct WeekViewModel
		{
			WeekViewModel();
			WeekViewModel(const std::string& name, Fl_Color color);

		public:
			std::string _name;
			Fl_Color _color;
		};

		WeekView();

		WeekViewModel _model;

	public:
		explicit WeekView(const WeekViewModel& model);

	public:

		std::string GetName() const;

		Fl_Color GetColor() const;

	public:

		static std::vector<std::shared_ptr<WeekView>> GetList();

	};

}

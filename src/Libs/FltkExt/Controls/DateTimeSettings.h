#pragma once
#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>

namespace FltkExt::Controls::Settings
{
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

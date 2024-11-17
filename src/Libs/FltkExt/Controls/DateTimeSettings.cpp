#include "DateTimeSettings.h"

namespace FltkExt::Controls::Settings
{
	WeekView::WeekViewModel::WeekViewModel() {
	}

	WeekView::WeekViewModel::WeekViewModel(const std::string& name, Fl_Color color)
		: _name(name)
		, _color(color) {
	}


	WeekView::WeekView()
	{
	}

	WeekView::WeekView(const WeekViewModel& model)
		: _model(model)
	{
	}

	std::string WeekView::GetName() const
	{
		return _model._name;
	}

	Fl_Color WeekView::GetColor() const
	{
		return _model._color;
	}

	std::vector<std::shared_ptr<WeekView>> WeekView::GetList()
	{
		static std::vector<std::shared_ptr<WeekView>> _instance;
		if (_instance.empty())
		{
			_instance.resize(7);
			_instance[0] = std::make_shared<WeekView>(WeekViewModel("Пн", fl_darker(FL_BLACK)));
			_instance[1] = std::make_shared<WeekView>(WeekViewModel("Вт", fl_darker(FL_BLACK)));
			_instance[2] = std::make_shared<WeekView>(WeekViewModel("Ср", fl_darker(FL_BLACK)));
			_instance[3] = std::make_shared<WeekView>(WeekViewModel("Чт", fl_darker(FL_BLACK)));
			_instance[4] = std::make_shared<WeekView>(WeekViewModel("Пт", fl_darker(FL_BLACK)));
			_instance[5] = std::make_shared<WeekView>(WeekViewModel("Сб", fl_darker(FL_RED)));
			_instance[6] = std::make_shared<WeekView>(WeekViewModel("Вс", fl_darker(FL_RED)));
		}

		return _instance;
	}

}

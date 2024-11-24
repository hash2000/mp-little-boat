#pragma once
#include "Common/core/Kernel.h"
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Data/DataStore.h"
#include "Libs/FltkExt/Data/DataTable.h"
#include <vector>

class MainWindowDataTable : public Fl_Double_Window
{
	using DataStore = FltkExt::Data::DataStore;
	using DataTable = FltkExt::Data::DataTable;
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using Flex = FltkExt::Containers::Flex;
	using Margin = FltkExt::Containers::Margin;
public:
	MainWindowDataTable(const char* label, const Ioc::Kernel& kernel)
		: Fl_Double_Window(800, 500, label)
	{
		_data = std::make_unique<DataStore>();

		auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
		fl->margin(Margin{ 20 });
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		{
			_table = std::make_shared<DataTable>(0, 0, 0, 0);

			auto bfl = new Flex{ 0, 0, 35, 35, Direction::Horz };
			bfl->margin(Margin{ 10, 5, 10, 5 });
			bfl->gap(10);
			{
				auto badd = new Fl_Button{ 0, 0, 80, 80, "add" };
				badd->callback(OnAddRecord, _data.get());

				bfl->end();
			}

			fl->end();
		}

		InitDate();
	}

	void InitDate()
	{
		_data->Append(_table);
		_data->SetProperties(
			{
				{ "columns-allow-header", true },
				{ "columns-height", 25 },
				{ "columns-allow-resizable", true },
				{ "columns-label-offset", 5 },
				{ "rows-allow-header", true },
				{ "rows-height", 80 },
				{ "rows-allow-resizable", true },
			});

		_data->SetModel(
			{
				{
					{ "name", "Name of person" },
					{ "type", "string" },
					{ "field", "Name" },
					{ "size", 100 },
					{ "align", "left" },
				},
				{
					{ "name", "Birth date" },
					{ "type", "datetime" },
					{ "format", "%Y-%m-%d %H:%M" },
					{ "field", "BirthDate" },
					{ "size", 250 },
				},
				{
					{ "name", "Phone" },
					{ "type", "string" },
					{ "field", "PhoneNumber" },
					{ "size", 120 },
				},
			});

	}

	static void OnAddRecord(Fl_Widget*, void* data)
	{
		static std::vector<FltkExt::Data::Rec> _records =
		{
			{
				{ "Name", "Иванов И. И." },
				{ "RussianName", "Иванов И. И." },
				{ "PhoneNumber", "+70000000000" },
				{ "BirthDate", Poco::DateTime {1952, 10, 7, 10, 20} },
				{ "Profession", "Какойто мужик на стройке" }
			},
			{
				{ "Name", "김 리" },
				{ "RussianName", "Ким Ли" },
				{ "PhoneNumber", "+70000000001" },
				{ "BirthDate", Poco::DateTime {1982, 1, 8, 12, 20} },
				{ "Profession", "Директор завода торпедных катеров" }
			},
			{
				{ "Name", "王丽" },
				{ "RussianName", "Ван Ли" },
				{ "PhoneNumber", "+70000000002" },
				{ "BirthDate", Poco::DateTime {1995, 8, 20, 22, 10} },
				{ "Profession", "CEO of Stark Industries" }
			},
			{
				{ "Name", "Tony Stark" },
				{ "RussianName", "Тони Старк" },
				{ "PhoneNumber", "+79994444444" },
				{ "BirthDate", Poco::DateTime {1995, 8, 20, 0, 0} },
				{ "Profession", "CEO of Stark Industries" }
			},
		};

		static int _recordNum = 0;

		auto ds = (DataStore*)data;
		ds->AddRecord(_records[_recordNum++]);

		if (_recordNum >= _records.size()) {
			_recordNum = 0;
		}
	}

private:
	std::unique_ptr<DataStore> _data;
	std::shared_ptr<DataTable> _table;
};

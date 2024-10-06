#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Data/DataStore.h"
#include "Libs/FltkExt/Data/DataTable.h"

using namespace FltkExt::Containers;
using namespace FltkExt::Data;

class MainWindowDataTable : public Fl_Double_Window
{
public:
	MainWindowDataTable()
		: Fl_Double_Window(800, 500, "Test FLTK UI")
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
				{ "allow_column_header", true },
				{ "allow_column_height", 25 },
				{ "allow_columns_resizable", true },
				{ "allow_row_header", true },
				{ "allow_row_height", 80 },
				{ "allow_rows_resizable", true },
			});

		_data->SetModel(
			{
				{
					{ "name", "Name of person" },
					{ "type", "string" },
					{ "field", "Name" },
					{ "size", 150 },
					{ "align", "left" },
				},
				{
					{ "name", "Birth date" },
					{ "type", "datetime" },
					{ "format", "yyyy-MM-dd HH:mm" },
					{ "field", "BirthDate" },
				},
				{
					{ "name", "Phone" },
					{ "type", "string" },
					{ "field", "PhoneNumber" },
				},
			});

	}

	static void OnAddRecord(Fl_Widget*, void* data)
	{
		auto ds = (DataStore*)data;
		ds->AddRecord({
			{ "Name", "Tony Stark" },
			{ "PhoneNumber", "+79994444444" },
			{ "BirthDate", Poco::DateTime {1995, 8, 20, 10, 10} },
			{ "Profession", "CEO of Stark Industries" }
			});

		ds->AddRecord({
			{ "Name", "Putin" },
			{ "PhoneNumber", "+70000000000" },
			{ "BirthDate", Poco::DateTime {1952, 10, 7, 10, 10} },
			{ "Profession", "President of the Russian Federation" }
			});
	}

private:
	std::unique_ptr<DataStore> _data;
	std::shared_ptr<DataTable> _table;
};

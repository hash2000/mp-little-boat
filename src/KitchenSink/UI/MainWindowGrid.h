#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Grid.h"
#include <sstream>

class MainWindowGrid : public Fl_Double_Window
{
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using Flex = FltkExt::Containers::Flex;
	using PushPosition = FltkExt::Containers::PushPosition;
	using Margin = FltkExt::Containers::Margin;
	using Grid = FltkExt::Containers::Grid;
	using GridRow = FltkExt::Containers::GridRow;
	using GridColumn = FltkExt::Containers::GridColumn;
	using GridPosition = FltkExt::Containers::GridPosition;
	using Alignment = FltkExt::Containers::Alignment;

public:
	MainWindowGrid(const char* label) : Fl_Double_Window(100, 100, 800, 600, label)
	{
		CreateFlexAndGrid();
	}

private:
	void CreateFlexAndGrid()
	{
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Horz };
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		fl->margin(Margin(10));
		{
			auto gr = new Grid{ 0, 0, 0, 0 };

			gr->AllowRowsIncrease(true);

			gr->AddRow(GridRow{ .height = 40, .gap = 5 });
			gr->AddRow(GridRow{ .height = 100, .gap = 10 });
			gr->AddRow(GridRow{ .height = 60, .gap = 0 });
			gr->AddRow(GridRow{ .height = 10, .gap = 0 });
			gr->AddRow(GridRow{ .height = 100, .gap = 3 });
			gr->AddRow(GridRow{ .height = 100, .gap = 3 });
			gr->AddRow(GridRow{ .height = 100, .gap = 3 });
			gr->AddRow(GridRow{ .height = 100, .gap = 3 });
			gr->AddRow(GridRow{ .height = 60, .gap = 3 });

			gr->AddColumn(GridColumn{ .width = 100, .gap = 5 });
			gr->AddColumn(GridColumn{ .width = 200, .gap = 5 });
			gr->AddColumn(GridColumn{ .width = 150, .gap = 0 });

			gr->box(FL_FREE_BOXTYPE);
			{
				// заполнение нескольких ячеек

				auto bbutton1 = new Fl_Button{ 0, 0, 0, 0, "bigbutton1" };
				gr->Attach(bbutton1,
					GridPosition{ .start = 0, .end = 2 },
					GridPosition{ .start = 1, .end = 2 });

				auto bbutton2 = new Fl_Button{ 0, 0, 0, 0, "bigbutton2" };
				gr->Attach(bbutton2,
					GridPosition{ .start = 0, .end = 2 },
					GridPosition{ .start = 0, .end = 0 });

				// заполнение и выравнивание
				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "center vert" };
					gr->Attach(b, 4, 0, Alignment::Center | Alignment::Vertical);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "center horz" };
					gr->Attach(b, 4, 1, Alignment::Center | Alignment::Horizontal);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "fill" };
					gr->Attach(b, 4, 2, Alignment::Fill);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "left" };
					gr->Attach(b, 5, 0, Alignment::Left);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "right" };
					gr->Attach(b, 5, 1, Alignment::Right);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "left right" };
					gr->Attach(b, 5, 2, Alignment::Left | Alignment::Right);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "top" };
					gr->Attach(b, 6, 0, Alignment::Top);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "bottom" };
					gr->Attach(b, 6, 1, Alignment::Bottom);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "top bottom" };
					gr->Attach(b, 6, 2, Alignment::Top | Alignment::Bottom);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "left top" };
					gr->Attach(b, 7, 0, Alignment::Left | Alignment::Top);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "left bottom" };
					gr->Attach(b, 7, 1, Alignment::Left | Alignment::Bottom);
				}

				{
					auto b = new Fl_Button{ 0, 0, 70, 30, "right top" };
					gr->Attach(b, 7, 2, Alignment::Right | Alignment::Top);
				}
				// автоматическое добавление строк

				char title[20];
				for (int i = 8; i < 100; i++)
				{
					std::sprintf(title, "bt%d", i - 3);

					auto b1c1 = new Fl_Button{ 0, 0, 0, 0 };
					b1c1->copy_label(title);
					gr->Attach(b1c1, i, 0);

					auto b2c1 = new Fl_Button{ 0, 0, 0, 0 };
					b2c1->copy_label(title);
					gr->Attach(b2c1, i, 1);

					auto b3c1 = new Fl_Button{ 0, 0, 0, 0 };
					b3c1->copy_label(title);
					gr->Attach(b3c1, i, 2);
				}

				gr->end();
			}

			fl->end();
		}

	}

};


#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/TabbedPanel.h"
#include "Libs/FltkExt/Containers/Layout.h"

#include <FL/Fl_Tabs.H>

class MainWindowPanel : public Fl_Double_Window
{
public:
	MainWindowPanel()
		: Fl_Double_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		begin();
		CreateTabPanel();
		end();
	}

	void TabsTest()
	{
		auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
		fl->box(FL_FREE_BOXTYPE);
		fl->SetLayoutStrategy(LayoutStrategy::Full);
		{
			// для нормального расчёра размеров элементу Fl_Group нужны начальные размеры,
			// а для того, чтобы Flex эти размеры не считал фиксированными для элемента управления
			// используется UseBounds false

			auto tabs = new Fl_Tabs{ 0, 0, w(), h() };
			fl->UseBounds(tabs, false);

			//tabs->resizable(nullptr);
			{
				auto g1 = new Flex{ 0, 0, w(), h() - 30, Direction::Horz };
				g1->SetLayoutStrategy(LayoutStrategy::Full);
				g1->label("firstTab");
				//g1->margin(Margin(0, 0, 0, 30));
				{
					auto b1 = new Fl_Button{ 100, 110, 100, 20, "g1b1" };
					auto b2 = new Fl_Button{ 100, 135, 100, 20, "g1b2" };
					auto b3 = new Fl_Button{ 100, 135, 100, 20, "g1b3" };

					g1->end();
				}

				auto g2 = new  Flex{ 0, 0,  w(), h() - 30, Direction::Horz };
				g2->SetLayoutStrategy(LayoutStrategy::Full);
				g2->label("secondTab");
				//g2->margin(Margin(0, 0, 0, 30));
				{
					auto b1 = new Fl_Button{ 100, 110, 100, 20, "g2b1" };
					auto b2 = new Fl_Button{ 100, 135, 100, 20, "g2b2" };
					auto b3 = new Fl_Button{ 100, 135, 100, 20, "g2b3" };

					g2->end();
				}
				tabs->end();
			}

			fl->end();
		}
	}

	void SizesTest()
	{
		auto g = new Fl_Group{ 20, 20, 200, 200 };
		g->box(FL_FREE_BOXTYPE);
		{
			auto b1 = new Fl_Box{ 10, 10, 10, 10 };
			b1->box(FL_FREE_BOXTYPE);
			b1->resize(30, 30, 10, 10);

			g->end();
		}
	}

	void CreateTabPanel()
	{
		auto layout = new Layout{ 0, 0, w(), h() };
		layout->box(FL_FREE_BOXTYPE);

		auto tabbed_panel_left = new TabbedPanel{ 300, "left" };
		tabbed_panel_left->SetMinPanelSize(15);
		{
			tabbed_panel_left->AttachContent("first", [&]() {
				auto btn1 = new Fl_Button(10, 10, 100, 16, "test1");
				auto btn2 = new Fl_Button(10, 10, 100, 16, "test2");
				auto btn3 = new Fl_Button(10, 10, 100, 16, "test3");
				});

			tabbed_panel_left->AttachContent("second", [&]() {
				auto btn = new Fl_Button(0, 0, 100, 16, "test2");
				});

			tabbed_panel_left->end();
		}

		layout->end();

		layout->Attach(tabbed_panel_left, Docking::Left);

	}

	void CreatePanels1()
	{

		auto layout = new Layout{ 0, 0, w(), h() };
		layout->box(FL_FREE_BOXTYPE);

		auto panel_left = new Panel{ 100, "left" };
		panel_left->box(FL_UP_BOX);
		panel_left->end();

		auto panel_left2 = new Panel{ 100, "left 2" };
		panel_left2->box(FL_UP_BOX);
		panel_left2->end();

		auto panel_top = new Panel{ 200, "top" };
		panel_top->box(FL_UP_BOX);
		panel_top->SetMinPanelSize(35);
		panel_top->end();


		auto panel_right = new Panel{ 100, "right" };
		panel_right->box(FL_UP_BOX);
		panel_right->SetMinPanelSize(15);
		panel_right->end();

		auto panel_bottom = new Panel{ 200, "bottom" };
		panel_bottom->box(FL_UP_BOX);
		panel_bottom->SetMinPanelSize(35);
		panel_bottom->end();

		auto panel_center = new Panel{ 0, "center" };
		panel_center->box(FL_UP_BOX);
		panel_center->end();

		layout->end();

		layout->Attach(panel_center, Docking::Center);
		layout->Attach(panel_top, Docking::Top);
		layout->Attach(panel_bottom, Docking::Bottom);
		layout->Attach(panel_right, Docking::Right);
		layout->Attach(panel_left, Docking::Left);
		layout->Attach(panel_left2, Docking::Left);
	}
};

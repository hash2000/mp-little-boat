#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/Layout.h"

class MainWindowPanel : public Fl_Double_Window
{
public:
	MainWindowPanel()
		: Fl_Double_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		begin();
		CreatePanels1();
		end();
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

	void CreatePanels1()
	{

		auto layout = new Layout{ 0, 0, w(), h() };
		layout->box(FL_FREE_BOXTYPE);


		auto panel_left = new Panel{ 100, "left" };
		panel_left->box(FL_UP_BOX);
		panel_left->SetMinPanelSize(15);
		panel_left->end();

		auto panel_left2 = new Panel{ 100, "left 2" };
		panel_left2->box(FL_UP_BOX);
		panel_left2->SetMinPanelSize(15);
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

		layout->AttachPanel(panel_center, Docking::Center);
		layout->AttachPanel(panel_top, Docking::Top);
		layout->AttachPanel(panel_bottom, Docking::Bottom);
		layout->AttachPanel(panel_right, Docking::Right);
		layout->AttachPanel(panel_left, Docking::Left);
		layout->AttachPanel(panel_left2, Docking::Left);
	}
};

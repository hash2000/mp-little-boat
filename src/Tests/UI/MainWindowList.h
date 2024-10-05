#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Layout.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/List.h"
#include <sstream>

using namespace FltkExt::Containers;



class MainWindowList : public Fl_Double_Window
{
public:
	MainWindowList() : Fl_Double_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		CreateList();
	}

private:
	void CreateList()
	{
		auto layout = new Layout{ 0, 0, w(), h() };
		layout->box(FL_FREE_BOXTYPE);
		{
			auto panel_left = new Panel{ 300, "left" };
			//panel_left->box(FL_UP_BOX);

			panel_left->begin();
			{
				auto lv = new List{ 0, 0, 0, 0, Direction::Vert };
				lv->box(FL_UP_BOX);
				//lv->margin(Margin(10));
				//lv->gap(5);
				{
					char title[20];
					for (int i = 0; i < 10; i++)
					{
						std::sprintf(title, "bt%d", i + 1);

						auto b = new Fl_Button{ 0, 0, 50, 30 };
						b->copy_label(title);

					}

					lv->end();
				}

				panel_left->end();
			}

			auto panel_bottom = new Panel{ 300, "botom" };
			panel_bottom->begin();
			{
				auto lv = new List{ 0, 0, 0, 0, Direction::Horz };
				lv->box(FL_UP_BOX);
				//lv->margin(Margin(10));
				//lv->gap(5);
				{
					char title[20];
					for (int i = 0; i < 10; i++)
					{
						std::sprintf(title, "bt%d", i + 1);

						auto b = new Fl_Button{ 0, 0, 50, 30 };
						b->copy_label(title);

					}

					lv->end();
				}

				panel_bottom->end();
			}

			layout->Attach(panel_left, Docking::Left);
			layout->Attach(panel_bottom, Docking::Bottom);
			layout->end();
		}
	}

};

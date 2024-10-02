#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"

class MyGroup : public Fl_Group
{
public:
	MyGroup(int cx, int cy, int cw, int ch)
		: Fl_Group(cx, cy, cw, ch)
	{
		box(FL_FREE_BOXTYPE);
	//	set_flag(CLIP_CHILDREN);
		begin();
	}
};


class MainWindowFlex : public Fl_Window
{
public:
	MainWindowFlex() : Fl_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		CreateTestToolbar();
	}

private:

	void CreateWindowWithChildren()
	{
		auto g1 = new MyGroup{ 20, 20, 200, 200 };
		{
			//resizable(g1);
			CreateWidget(0, 0, 40, 40, FL_RED, "test");
			g1->end();
		}
	}

	void CreateFlexTest()
	{
		auto fh1 = new Flex{ 0, 0, w(), h(), Direction::Horz };
		fh1->resizable(nullptr);
		fh1->box(FL_FREE_BOXTYPE);
		fh1->SetLayoutStrategy(LayoutStrategy::Full);
		{
			CreateWidget(0, 0, 40, 40, FL_RED, "fh1b1");
			CreateWidget(0, 0, 40, 40, FL_GREEN, "fh1b2");
			auto fv1 = new Flex{ 0, 0, 0, 0, Direction::Vert, PushPosition::End };
			fv1->box(FL_FREE_BOXTYPE);
			fv1->SetLayoutStrategy(LayoutStrategy::Full);
			fv1->margin(Margin(2));
			{
				auto f = new Flex{ 0, 0, 40, 40, Direction::Horz, PushPosition::End };
				f->box(FL_FREE_BOXTYPE);
				{
					CreateWidget(0, 0, 40, 40, FL_RED, "fb1");
					CreateWidget(0, 0, 40, 40, FL_GREEN, "fb2");
					CreateWidget(0, 0, 40, 40, FL_BLUE, "fb3");
					CreateWidget(0, 0, 40, 40, FL_BLACK, "fb4");
					CreateWidget(0, 0, 40, 40, FL_DARK_MAGENTA, "fb5");
					f->end();
				}
				fv1->end();
			}
			fh1->end();
		}
	}

	void CreateTestToolbar()
	{
		auto centerfl = new Flex{ 0, 0, w(), h(), Direction::Vert };
		centerfl->SetLayoutStrategy(LayoutStrategy::Full);
		centerfl->box(FL_FREE_BOXTYPE);
		{
			auto toolbar = new Flex{ 0, 0, 40, 40, Direction::Horz, PushPosition::End };
			{
				toolbar->box(FL_FREE_BOXTYPE);
				toolbar->gap(5);
				toolbar->margin(Margin(2));

				toolbar->UseBounds(CreateWidget(0, 0, 40, 40, FL_RED, "tbbtn1"), false);
				CreateWidget(0, 0, 50, 50, FL_DARK_GREEN, "tbbtn2");
				//CreateWidget(0, 0, 50, 50, FL_BLUE, "tbbtn3");
				//CreateWidget(0, 0, 0, 0, FL_DARK_RED, "tbbtn4");

				toolbar->end();
			}


			auto horzContent = new Flex{ 0, 0, 0, 0, Direction::Horz };
			{
				horzContent->box(FL_FREE_BOXTYPE);
				horzContent->SetLayoutStrategy(LayoutStrategy::Full);
				auto leftbar1 = new Flex{ 0, 0, 40, 40, Direction::Vert };
				{
					leftbar1->box(FL_FREE_BOXTYPE);
					leftbar1->margin(Margin{ 4 });
					CreateWidget(0, 0, 40, 40, FL_RED, "btn1");
					CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "btn2");
					CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");

					leftbar1->end();
				}

				auto leftbar2 = new Flex{ 0, 0, 40, 40, Direction::Vert, PushPosition::End };
				{
					leftbar2->box(FL_FREE_BOXTYPE);
					leftbar2->margin(Margin{ 4 });
					CreateWidget(0, 0, 40, 40, FL_RED, "lb2btn1");
					CreateWidget(0, 0, 50, 50, FL_DARK_GREEN, "lb2btn2");
					CreateWidget(0, 0, 50, 50, FL_BLUE, "lb2btn3");
					CreateWidget(0, 0, 0, 0, FL_DARK_RED, "lb2btn4");

					leftbar2->end();
				}

				auto leftbar3 = new Flex{ 0, 0, 40, 40, Direction::Vert };
				{
					leftbar3->box(FL_FREE_BOXTYPE);
					leftbar3->margin(Margin{ 4 });
					CreateWidget(0, 0, 40, 40, FL_RED, "lb3btn1");
					CreateWidget(0, 0, 50, 50, FL_DARK_GREEN, "lb3btn2");
					CreateWidget(0, 0, 50, 50, FL_BLUE, "lb3btn3");
					CreateWidget(0, 0, 0, 0, FL_DARK_RED, "lb3btn4");

					leftbar3->end();
				}

				auto innerFull = new Flex{ 0, 0, 0, 0, Direction::Horz };
				{
					innerFull->box(FL_FREE_BOXTYPE);
					innerFull->SetLayoutStrategy(LayoutStrategy::Full);
					auto horzinner = new Flex{ 0, 0, 0, 40, Direction::Horz };
					{
						horzinner->box(FL_FREE_BOXTYPE);

						CreateWidget(0, 0, 40, 40, FL_RED, "hbtn1");
						CreateWidget(0, 0, 50, 50, FL_DARK_GREEN, "hbtn2");
						CreateWidget(0, 0, 0, 0, FL_DARK_RED, "hbtn4");

						horzinner->end();
					}

					innerFull->end();
				}

				horzContent->end();
			}

			auto statusbar = new Flex{ 0, 0, 20, 20, Direction::Horz };
			{
				statusbar->box(FL_FREE_BOXTYPE);
				statusbar->gap(5);
				statusbar->margin(Margin(2));

				CreateWidget(0, 0, 40, 40, FL_RED, "sbbtn1");
				CreateWidget(0, 0, 0, 0, FL_DARK_GREEN, "sbbtn2");
				CreateWidget(0, 0, 0, 0, FL_BLUE, "btn3");
				CreateWidget(0, 0, 0, 0, FL_DARK_RED, "btn4");

				statusbar->end();
			}

			centerfl->end();
		}
	}

	Fl_Widget* CreateWidget(int cx, int cy, int cw, int ch, Fl_Color color, const char* title)
	{
		auto result = new Fl_Box{ cx, cy, cw, ch, title };
		result->color(fl_lighter(color));
		result->box(FL_FREE_BOXTYPE);
		return result;
	}
};

#pragma once
#include "Common/core/Kernel.h"
#include "FltkAll.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <stdlib.h>	/* qsort(3), srand(3).. */
#include <time.h>	/* time(2) */

static const int MAX_ROWS = 2000;
static const int MAX_FIELDS = 5;
static const int FIELD_WIDTH = 70;
static const int FIELD_HEIGHT = 30;

class MyData : public Fl_Group {
	Fl_Input* fields[MAX_FIELDS];
public:
	MyData(int X, int Y, int W, int H) : Fl_Group(X, Y, W, H) {
		static unsigned int colors[MAX_FIELDS] = {
			0xffffdd00, 0xffdddd00, 0xddffff00, 0xddffdd00, 0xddddff00
		};
		for (int t = 0; t < MAX_FIELDS; t++) {
			fields[t] = new Fl_Input(X + t * FIELD_WIDTH, Y, FIELD_WIDTH, H);
			fields[t]->color(Fl_Color(colors[t]));
		}
		end();
	}
	void SetData(int col, const char* val) {
		if (col >= 0 && col < MAX_FIELDS)
			fields[col]->value(val);
	}
};

struct SortedTreeUserData {
	Fl_Tree* tree;
	int direction;
};

class MainWindowFltkTree : public Fl_Double_Window
{
public:
	MainWindowFltkTree(const char* label, const Ioc::Kernel& kernel)
		: Fl_Double_Window(800, 600, label)
	{

		//TreeAsContainerTest();
		TreeCustomSortTest();
	}

private:


	// Resort the tree
	static void MySortCallback(Fl_Widget*, void* data) {
		auto userData = (SortedTreeUserData*)data;
		auto dir = userData->direction;		// forward or reverse
		auto _tree = userData->tree;
		Fl_Tree_Item* i = _tree->root();
		// Bubble sort
		for (int ax = 0; ax < i->children(); ax++) {
			for (int bx = ax + 1; bx < i->children(); bx++) {
				long a; sscanf(i->child(ax)->label(), "%ld", &a);
				long b; sscanf(i->child(bx)->label(), "%ld", &b);
				switch (dir) {
				case  1: if (a > b) { i->swap_children(ax, bx); } break; // fwd
				case -1: if (a < b) { i->swap_children(ax, bx); } break; // rev
				}
			}
		}
		_tree->redraw();
	}



	void TreeCustomSortTest()
	{
		auto _tree = new Fl_Tree(10, 10, w() - 20, h() - 60);

		_tree->showroot(1);
		time_t tval; time(&tval);
		srand((unsigned)tval);

		// Add 200 random numbers to the tree
		char word[50];
		for (int t = 0; t < 200; t++) {
			sprintf(word, "%ld", long((float(rand()) / RAND_MAX) * 1000000));
			_tree->add(word);
		}

		// Add some sort buttons
		auto bt1 = new Fl_Button(10, h() - 40, 80, 20, "Fwd");
		auto bt1Data = new SortedTreeUserData{ .tree = _tree, .direction = 1 };
		bt1->callback(MySortCallback, (void*)bt1Data);

		auto bt2 = new Fl_Button(20 + 80, h() - 40, 80, 20, "Rev");
		auto bt2Data = new SortedTreeUserData{ .tree = _tree, .direction = -1 };
		bt2->callback(MySortCallback, (void*)bt2Data);
	}

	void TreeAsContainerTest()
	{
		auto _tree = new Fl_Tree(10, 10, w() - 20, h() - 20);
		// Create the tree
		_tree->showroot(0);				// don't show root of tree
		// Add some regular text nodes
		_tree->add("Foo/Bar/001");
		_tree->add("Foo/Bar/002");
		_tree->add("Foo/Bla/Aaa");
		_tree->add("Foo/Bla/Bbb");
		// Add items to the 'Data' node
		for (int t = 0; t < MAX_ROWS; t++) {
			// Add item to tree
			static char s[80];
			sprintf(s, "FLTK Widgets/%d", t);
			Fl_Tree_Item* item = _tree->add(s);
			// Reconfigure item to be an FLTK widget (MyData)
			_tree->begin();
			{
				MyData* data = new MyData(0, 0, FIELD_WIDTH * MAX_FIELDS, FIELD_HEIGHT);
				item->widget(data);
				// Initialize widget data
				for (int c = 0; c < MAX_FIELDS; c++) {
					sprintf(s, "%d-%d", t, c);
					data->SetData(c, s);
				}
			}
			_tree->end();
		}
	}

};

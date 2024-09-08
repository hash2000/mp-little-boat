#pragma once
#include "FltkAll.h"

constexpr double PI = 3.14159;

class MyTable : public Fl_Table {
	const char* mode;
public:
	MyTable(int X, int Y, int W, int H, const char* mode) : Fl_Table(X, Y, W, H) {
		rows(11);
		row_height_all(20);
		row_header(1);

		cols(11);
		col_width_all(60);
		col_header(1);
		col_resize(1);
		// enable column resizing
		this->mode = mode;
		end();
	}
	void resize(int X, int Y, int W, int H) override {
		if (W > 718)
			W = 718;                   // don't exceed 700 in width
		Fl_Table::resize(X, Y, W, h());              // disallow changes in height
	}
	// Handle drawing table's cells
	//     Fl_Table calls this function to draw each visible cell in the table.
	//     It's up to us to use FLTK's drawing functions to draw the cells the way we want.
	//
	void draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H) override {
		static char s[40];
		switch (context) {
		case CONTEXT_STARTPAGE:         // before page is drawn..
			fl_font(FL_HELVETICA, 10);    // set the font for our drawing operations
			return;
		case CONTEXT_COL_HEADER:        // Drawing column/row headers
		case CONTEXT_ROW_HEADER: {
			int val = context == CONTEXT_COL_HEADER ? COL : ROW;
			int col = context == CONTEXT_COL_HEADER ? col_header_color() : row_header_color();
			fl_push_clip(X, Y, W, H);
			if (strcmp(mode, "SinCos") == 0) { sprintf(s, "%.2f", ((val / 10.0) * PI)); }
			else sprintf(s, "%d", val);
			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col);
			fl_color(FL_BLACK);
			fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
			fl_pop_clip();
			return;
		}
		case CONTEXT_CELL: {            // Draw data in cells
			int col = is_selected(ROW, COL) ? FL_YELLOW : FL_WHITE;
			fl_push_clip(X, Y, W, H);
			if (strcmp(mode, "Addition") == 0) {
				sprintf(s, "%d", ROW + COL);
			}
			else
				if (strcmp(mode, "Subtract") == 0) {
					sprintf(s, "%d", ROW - COL);
				}
				else
					if (strcmp(mode, "Multiply") == 0) {
						sprintf(s, "%d", ROW * COL);
					}
					else
						if (strcmp(mode, "Divide") == 0) {
							if (COL == 0)
								sprintf(s, "N/A");
							else
								sprintf(s, "%.2f", (float)ROW / (float)COL);
						}
						else
							if (strcmp(mode, "Exponent") == 0) {
								sprintf(s, "%g", powf((float)ROW, (float)COL));
							}
							else
								if (strcmp(mode, "SinCos") == 0) {
									sprintf(s, "%.2f", sin((ROW / 10.0) * PI) * cos((COL / 10.0) * PI));
								}
								else
								{
									sprintf(s, "???");
								}

			fl_color(col); fl_rectf(X, Y, W, H);                               // bg
			fl_color(FL_GRAY0); fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);       // text
			fl_color(color());  fl_rect(X, Y, W, H);                           // box
			fl_pop_clip();
			return;
		}
		default:
			return;
		}
	}
};

class MainWindowFltkTreeOfTables : public Fl_Double_Window
{
public:
	MainWindowFltkTreeOfTables() : Fl_Double_Window(100, 100, 800, 600, "Test FLTK UI")
	{
		begin();
		{
			// Create tree
			Fl_Tree* tree = new Fl_Tree(10, 10, w() - 20, h() - 20);
			tree->root()->label("Math Tables");
			tree->item_labelfont(FL_COURIER);           // font to use for items
			tree->linespacing(4);                       // extra space between items
			//tree->item_draw_mode(tree->item_draw_mode() |
			//	FL_TREE_ITEM_DRAW_LABEL_AND_WIDGET |    // draw item with widget() next to it
			//	FL_TREE_ITEM_HEIGHT_FROM_WIDGET);       // make item height follow table's height
			tree->selectmode(FL_TREE_SELECT_NONE);      // font to use for items
			//tree->widgetmarginleft(12);                 // space between item and table
			tree->connectorstyle(FL_TREE_CONNECTOR_DOTTED);

			// Create tables, assign each a tree item
			tree->begin();
			{
				MyTable* table;
				Fl_Tree_Item* item;

				table = new MyTable(0, 0, 500, 156, "Addition");
				item = tree->add("Arithmetic/Addition");
				item->widget(table);

				table = new MyTable(0, 0, 500, 156, "Subtract");
				item = tree->add("Arithmetic/Subtract");
				item->widget(table);

				table = new MyTable(0, 0, 500, 156, "Multiply");
				item = tree->add("Arithmetic/Multiply");
				item->widget(table);

				table = new MyTable(0, 0, 500, 156, "Divide");
				item = tree->add("Arithmetic/Divide  ");
				item->widget(table);

				table = new MyTable(0, 0, 500, 156, "Exponent");
				item = tree->add("Misc/Exponent");
				item->widget(table);

				table = new MyTable(0, 0, 500, 156, "SinCos");
				item = tree->add("Misc/Sin*Cos ");
				item->widget(table);
			}
			tree->end();

		}
		end();
		resizable(this);
	}
};

#pragma once
#include "FltkAll.h"

#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>


namespace
{
	//
	// Simple demonstration class deriving from Fl_Table
	//
	class WidgetTable : public Fl_Table {
	public:
		WidgetTable(int x, int y, int w, int h, const char* l = 0) : Fl_Table(x, y, w, h, l) {
			col_header(1);
			col_resize(1);
			col_header_height(25);
			row_header(1);
			row_resize(1);
			row_header_width(80);
			end();
		}
		~WidgetTable() { }

		void SetSize(int newrows, int newcols) {
			clear();            // clear any previous widgets, if any
			rows(newrows);
			cols(newcols);

			begin();            // start adding widgets to group
			{
				for (int r = 0; r < newrows; r++) {
					for (int c = 0; c < newcols; c++) {
						int X, Y, W, H;
						find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);

						char s[40];
						if (c & 1) {
							// Create the input widgets
							sprintf(s, "%d.%d", r, c);
							Fl_Input* in = new Fl_Input(X, Y, W, H);
							in->value(s);
						}
						else {
							// Create the light buttons
							sprintf(s, "%d/%d ", r, c);
							Fl_Light_Button* butt = new Fl_Light_Button(X, Y, W, H);
							butt->copy_label(s);
							butt->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
							butt->callback([](Fl_Widget* w, void*) {
								fprintf(stderr, "BUTTON: %s\n", (const char*)w->label());
								}, (void*)0);
							butt->value(((r + c * 2) & 4) ? 1 : 0);
						}
					}
				}
			}
			end();
		}

	protected:
		void draw_cell(TableContext context,                  // table cell drawing
			int R = 0, int C = 0, int X = 0, int Y = 0, int W = 0, int H = 0) override;


	};

	// Handle drawing all cells in table
	void WidgetTable::draw_cell(TableContext context,
		int R, int C, int X, int Y, int W, int H) {
		switch (context) {
		case CONTEXT_STARTPAGE:
			fl_font(FL_HELVETICA, 12);                // font used by all headers
			break;

		case CONTEXT_RC_RESIZE: {
			int X, Y, W, H;
			int index = 0;
			for (int r = 0; r < rows(); r++) {
				for (int c = 0; c < cols(); c++) {
					if (index >= children()) break;
					find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
					child(index++)->resize(X, Y, W, H);
				}
			}
			init_sizes();                     // tell group children resized
			return;
		}

		case CONTEXT_ROW_HEADER:
			fl_push_clip(X, Y, W, H);
			{
				static char s[40];
				sprintf(s, "Row %d", R);
				fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
				fl_color(FL_BLACK);
				fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
			}
			fl_pop_clip();
			return;

		case CONTEXT_COL_HEADER:
			fl_push_clip(X, Y, W, H);
			{
				static char s[40];
				sprintf(s, "Column %d", C);
				fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
				fl_color(FL_BLACK);
				fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
			}
			fl_pop_clip();
			return;

		case CONTEXT_CELL:
			return;           // fltk handles drawing the widgets

		default:
			return;
		}
	}
}


class MainWindowFltkTable : public Fl_Double_Window
{
public:
	MainWindowFltkTable(const char* label) : Fl_Double_Window(100, 100, 940, 600, label)
	{
		auto table = new WidgetTable { 20, 20, w() - 40, h() - 40, "FLTK widget table" };
		table->SetSize(50, 50);
		resizable(table);
		end();
	}

};

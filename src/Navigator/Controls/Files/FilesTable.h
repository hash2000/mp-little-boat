#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>

class FilesTable : public Fl_Table
{
public:
	FilesTable(int cx, int cy, int cw, int ch);

protected:

	void draw_cell(TableContext context, int r, int c, int cx, int cy, int cw, int ch) override;

};

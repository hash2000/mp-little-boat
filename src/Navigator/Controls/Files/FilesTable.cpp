#include "FilesTable.h"

FilesTable::FilesTable(int cx, int cy, int cw, int ch)
	: Fl_Table(cx, cy, cw, ch)
{
	col_header(1);
	col_resize(1);
	col_header_height(25);
	row_header(0);
	row_resize(0);
	row_header_width(80);
	end();
}

void FilesTable::draw_cell(TableContext context, int r, int c, int cx, int cy, int cw, int ch)
{
	switch (context)
	{
	case CONTEXT_STARTPAGE:
		// font used by all headers
		fl_font(FL_HELVETICA, 12);
		break;
	}
}

#include "DataTable.h"

namespace FltkExt::Data
{
	DataTable::DataTable(int cx, int cy, int cw, int ch)
		: Fl_Table(cx, cy, cw, ch)
	{
		end();
	}

	void DataTable::draw_cell(TableContext context, int r, int c, int cx, int cy, int cw, int ch)
	{
		switch (context)
		{
		case CONTEXT_STARTPAGE:
			// font used by all headers
			fl_font(FL_HELVETICA, 12);
			break;

		case CONTEXT_RC_RESIZE:
			OnColumnOrRowResized(r, c);
			break;
		case CONTEXT_ROW_HEADER:
			OnDrawRowHeader(r, cx, cy, cw, ch);
			break;
		case CONTEXT_COL_HEADER:
			OnDrawColumnHeader(c, cx, cy, cw, ch);
			break;
		case CONTEXT_CELL:
			// fltk handles drawing the widgets
			return;

		}
	}

	void DataTable::OnColumnOrRowResized(int r, int c)
	{
		int cx, cy, cw, ch;
		int index = 0;
		for (int r = 0; r < rows(); r++) {
			for (int c = 0; c < cols(); c++) {
				if (index >= children()) {
					break;
				}
				find_cell(CONTEXT_TABLE, r, c, cx, cy, cw, ch);
				child(index++)->resize(cx, cy, cw, ch);
			}
		}

		// tell group children resized
		init_sizes();
	}

	void DataTable::OnDrawRowHeader(int r, int cx, int cy, int cw, int ch)
	{
		fl_push_clip(cx, cy, cw, ch);
		{
			static char s[40];
			sprintf(s, "Row %d", r);
			fl_draw_box(FL_THIN_UP_BOX, cx, cy, cw, ch, row_header_color());
			fl_color(FL_BLACK);
			fl_draw(s, cx, cy, cw, ch, FL_ALIGN_CENTER);
		}
		fl_pop_clip();
	}

	void DataTable::OnDrawColumnHeader(int c, int cx, int cy, int cw, int ch)
	{
		auto it = std::next(_model.begin(), c);
		if (it == _model.end()) {
			return;
		}

		auto model = *it;
		auto name = model.GetValue<std::string>("name", "");
		auto align = GetAlignFromString(model.GetValue<std::string>("align", "center"));

		fl_push_clip(cx, cy, cw, ch);
		{
			fl_draw_box(FL_THIN_UP_BOX, cx, cy, cw, ch, col_header_color());
			fl_color(FL_BLACK);
			fl_draw(name.c_str(), cx, cy, cw, ch, align);
		}
		fl_pop_clip();
	}

	Fl_Align DataTable::GetAlignFromString(const std::string& name, Fl_Align defaultAlign) const
	{
		if (name == "center") {
			return FL_ALIGN_CENTER;
		}
		else if (name == "bottom") {
			return FL_ALIGN_BOTTOM;
		}
		else if (name == "top") {
			return FL_ALIGN_TOP;
		}
		else if (name == "left") {
			return FL_ALIGN_LEFT;
		}
		else if (name == "left_bottom") {
			return FL_ALIGN_LEFT_BOTTOM;
		}
		else if (name == "left_top") {
			return FL_ALIGN_LEFT_TOP;
		}
		else if (name == "right") {
			return FL_ALIGN_RIGHT;
		}
		else if (name == "right_bottom") {
			return FL_ALIGN_RIGHT_BOTTOM;
		}
		else if (name == "right_top") {
			return FL_ALIGN_RIGHT_TOP;
		}

		return defaultAlign;
	}

	void DataTable::ApplyProperties(const Props& props)
	{
		begin();

		col_resize(props.GetValue<bool>("allow_columns_resizable", false) ? 1 : 0);
		col_header(props.GetValue<bool>("allow_column_header", false) ? 1 : 0);
		col_header_height(props.GetValue<int>("allow_column_height", 25));

		row_resize(props.GetValue<bool>("allow_rows_resizable", false) ? 1 : 0);
		row_header(props.GetValue<bool>("allow_row_header", false) ? 1 : 0);
		row_header_width(props.GetValue<int>("allow_row_height", 80));

		end();
	}

	void DataTable::ApplyModel(const Model& model)
	{
		_model = model;
		cols(_model.size());

		int index = 0;
		for (auto field : model)
		{
			auto size = field.GetValue<int>("size", 80);
			col_width(index, size);
			index++;
		}
	}

	void DataTable::ApplyRecord(const Rec& rec)
	{
		auto row = rows();
		rows(row + 1);
		begin();

		int cx, cy, cw, ch;
		int col = 0;

		for (auto recval : rec)
		{
			if (find_cell(CONTEXT_TABLE, row, col, cx, cy, cw, ch) != -1)
			{
				auto fieldText = recval.second.convert<std::string>();
				auto box = new Fl_Box{ cx, cy, cw, ch };
				box->copy_label(fieldText.c_str());
				box->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
			}

			col++;
		}

		end();
	}

	void DataTable::ClearRecodrs()
	{
		clear();
	}

}
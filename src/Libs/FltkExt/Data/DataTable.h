#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>
#include "Libs/FltkExt/Data/IDataListener.h"
#include <string>

namespace FltkExt::Data
{
	class DataTable : public IDataListener, public Fl_Table
	{
	public:
		DataTable(int cx, int cy, int cw, int ch);

	public:

		void ApplyProperties(const Props& props) override;

		void ApplyModel(const Model& model) override;

		void ApplyRecord(const Rec& rec) override;

	protected:

		void draw_cell(TableContext context, int r, int c, int cx, int cy, int cw, int ch) override;

	private:

		void OnColumnOrRowResized(int r, int c);

		void OnDrawRowHeader(int r, int cx, int cy, int cw, int ch);

		void OnDrawColumnHeader(int c, int cx, int cy, int cw, int ch);

		Fl_Align GetAlignFromString(const std::string& name, Fl_Align defaultAlign = FL_ALIGN_CENTER) const;

	private:

		Model _model;
	};
}

#pragma once
#include <FL/Fl.H>
#include "Libs/FltkExt/Containers/BaseScrolledGrid.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <list>
#include <vector>
#include <memory>

namespace FltkExt::Containers
{


	struct GridRow {
		int height = 50;
		int gap = 0;
	};

	struct GridColumn {
		int width = 50;
		int gap = 0;
	};

	struct GridPosition {
		int start = 0;
		int end = 0;
	};

	class Grid : public BaseScrolledGrid
	{
	public:
		Grid(int cx, int cy, int cw, int ch);

		void AddRow(const GridRow& row);

		void AddColumn(const GridColumn& col);

		void Attach(Fl_Widget* widget, int row, int column, Alignment::Type align = Alignment::Fill);

		void Attach(Fl_Widget* widget, const GridPosition& row, const GridPosition& column, Alignment::Type align = Alignment::Fill);

		void AllowRowsIncrease(bool allow);

		void AllowColumnsIncrease(bool allow);

		int GetRowsCount() const override;

		int GetColumnsCount() const override;

		int GetRowHeight(int row) const override;

		int GetColumnWidth(int columns) const override;

	private:

		void AdjustLayout(int cx, int cy, int cw, int ch) override;

		bool ApplyRows(const GridPosition& rows);

		bool ApplyColumns(const GridPosition& columns);

	private:

		struct ElementContext {
			Fl_Widget* widget = nullptr;
			GridPosition row;
			GridPosition column;
			Alignment::Type align = Alignment::Fill;
		};

	private:

		bool _allowRowsIncrease = false;
		bool _allowColumnsIncrease = false;

		std::list<std::shared_ptr<ElementContext>> _items;
		std::vector<std::shared_ptr<GridRow>> _rows;
		std::vector<std::shared_ptr<GridColumn>> _columns;
	};

}

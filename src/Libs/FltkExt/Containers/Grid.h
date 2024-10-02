#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <list>
#include <vector>
#include <memory>

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

class Grid : public Container
{
public:
	Grid(int cx, int cy, int cw, int ch);

	const Margin& margin() const;

	void margin(const Margin& m);

	void AddRow(const GridRow& row);

	void AddColumn(const GridColumn& col);

	void AddWidget(Fl_Widget* widget, int row, int column, Alignment::Type align = Alignment::Fill);

	void AddWidget(Fl_Widget* widget, const GridPosition& row, const GridPosition& column, Alignment::Type align = Alignment::Fill);

	void end() override;

	void AllowRowsIncrease(bool allow);

	void AllowColumnsIncrease(bool allow);

private:

	struct ElementContext {
		Fl_Widget* widget = nullptr;
		GridPosition row;
		GridPosition column;
		Alignment::Type align = Alignment::Fill;
	};

private:

	void AdjustLayout(int cx, int cy, int cw, int ch) override;

	bool ApplyRows(const GridPosition& rows);

	bool ApplyColumns(const GridPosition& columns);

	void RecalcArea();

	void RecalcRowsOffsets();

	void RecalcColumnsOffsets();

	long GetRowScrollPos(int row);

	long GetColumnScrollPos(int column);

private:

	static void OnScroll(Fl_Widget* widget, void* data);

	void OnGridScrilled();

	void OnGridResized();

private:
	int _areax = 0;
	int _areay = 0;
	int _areaw = 0;
	int _areah = 0;
	int _areaVirtW = 0;
	int _areaVirtH = 0;

	int _rowPosition = 0;
	int _topRow = 0;
	int _topRowScrollpos = -1;
	int _bottomRow = 0;

	int _colPosition = 0;
	int _leftCol = 0;
	int _leftColScrollpos = -1;
	int _rightCol = 0;

	bool _allowRowsIncrease = false;
	bool _allowColumnsIncrease = false;
	Margin _margin;

	std::unique_ptr<Fl_Scroll> _area;
	std::unique_ptr<Fl_Scrollbar> _vscroll;
	std::unique_ptr<Fl_Scrollbar> _hscroll;

	std::list<std::shared_ptr<ElementContext>> _items;
	std::vector<std::shared_ptr<GridRow>> _rows;
	std::vector<std::shared_ptr<GridColumn>> _columns;
};

#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include "Libs/FltkExt/Containers/Container.h"

class BaseScrolledGrid : public Container
{
public:
	BaseScrolledGrid(int cx, int cy, int cw, int ch);

	const Margin& margin() const;

	void margin(const Margin& m);

	void end() override;

	virtual int GetRowsCount() const = 0;

	virtual int GetColumnsCount() const = 0;

	virtual int GetRowHeight(int row) const = 0;

	virtual int GetColumnWidth(int columns) const = 0;

private:

	static void OnScroll(Fl_Widget* widget, void* data);

	void OnGridScrilled();

	void OnGridResized();

	void RecalcArea();

	void RecalcRowsOffsets();

	void RecalcColumnsOffsets();

	long GetRowScrollPos(int row);

	long GetColumnScrollPos(int column);

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

	Margin _margin;

	std::unique_ptr<Fl_Scroll> _area;
	std::unique_ptr<Fl_Scrollbar> _vscroll;
	std::unique_ptr<Fl_Scrollbar> _hscroll;
};

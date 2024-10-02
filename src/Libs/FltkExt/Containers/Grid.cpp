#include "Grid.h"
#include <FL/fl_draw.H>
#include <algorithm>

Grid::Grid(int cx, int cy, int cw, int ch)
	: Container(cx, cy, cw, ch)
{
	_vscroll = std::make_unique<Fl_Scrollbar>(0, 0, 0, 0);
	_vscroll->type(FL_VERTICAL);
	_vscroll->callback(OnScroll, this);

	_hscroll = std::make_unique<Fl_Scrollbar>(0, 0, 0, 0);
	_hscroll->type(FL_HORIZONTAL);
	_hscroll->callback(OnScroll, this);

	_area = std::make_unique<Fl_Scroll>(0, 0, 0, 0);
	_area->box(FL_NO_BOX);
	_area->type(0);
	_area->box(FL_FREE_BOXTYPE);
	_area->hide();
	_area->end();

	end();

	_area->begin();
}

const Margin& Grid::margin() const
{
	return _margin;
}

void Grid::margin(const Margin& m)
{
	_margin = m;
	RecalcLayout();
}

void Grid::AllowRowsIncrease(bool allow)
{
	_allowRowsIncrease = allow;
}

void Grid::AllowColumnsIncrease(bool allow)
{
	_allowColumnsIncrease = allow;
}

void Grid::AddRow(const GridRow& row)
{
	auto pRow = std::make_shared<GridRow>();
	pRow->height = row.height < 0 ? 0 : row.height;
	pRow->gap = row.gap < 0 ? 0 : row.gap;

	_rows.push_back(pRow);

	RecalcLayout();
}

void Grid::AddColumn(const GridColumn& col)
{
	auto pColumn = std::make_shared<GridColumn>();
	pColumn->width = col.width < 0 ? 0 : col.width;
	pColumn->gap = col.gap < 0 ? 0 : col.gap;

	_columns.push_back(pColumn);

	RecalcLayout();
}

bool Grid::ApplyRows(const GridPosition& rows)
{
	if (!_allowRowsIncrease) {
		return false;
	}

	if (rows.start > rows.end) {
		return false;
	}

	std::shared_ptr<GridRow> pRowTemplate;
	if (!_rows.empty()) {
		pRowTemplate = *_rows.rbegin();
	}

	for (auto i = _rows.size(); i <= rows.end; i++)
	{
		auto pRow = std::make_shared<GridRow>();
		if (pRowTemplate) {
			pRow->height = pRowTemplate->height;
			pRow->gap = pRowTemplate->gap;
		}

		_rows.push_back(pRow);
	}

	RecalcLayout();

	return true;
}

bool Grid::ApplyColumns(const GridPosition& columns)
{

	return _allowColumnsIncrease;
}

void Grid::AddWidget(Fl_Widget* widget, int row, int column)
{
	AddWidget(widget,
		GridPosition{ .start = row, .end = row },
		GridPosition{ .start = column, .end = column });
}

void Grid::AddWidget(Fl_Widget* widget,
	const GridPosition& row,
	const GridPosition& column)
{
	auto child = _area->find(widget);
	if (child >= _area->children()) {
		return;
	}

	if (row.start < 0 || row.end < 0 || column.start < 0 || column.end < 0) {
		return;
	}

	if (row.start > row.end || column.start > column.end) {
		return;
	}

	if (row.end >= _rows.size()) {
		if (!ApplyRows(row)) {
			return;
		}
	}

	if (column.end >= _columns.size()) {
		if (!ApplyColumns(column)) {
			return;
		}
	}

	auto pWidget = std::make_shared<ElementContext>();
	pWidget->widget = widget;
	pWidget->row.start = row.start;
	pWidget->row.end = row.end;
	pWidget->column.start = column.start;
	pWidget->column.end = column.end;

	_items.push_back(pWidget);

	RecalcLayout();
}

void Grid::OnScroll(Fl_Widget* widget, void* data)
{
	auto me = (Grid*)data;
	me->RecalcArea();
	me->OnGridScrilled();
	me->RecalcLayout();
	me->redraw();
}

void Grid::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::AdjustLayout(cx, cy, cw, ch);

	RecalcArea();

	if (_rows.size() == 0 || _columns.size() == 0) {
		return;
	}

	auto sx = x() + Fl::box_dx(box()) + Fl::box_dx(_area->box()) + _margin.left - _hscroll->value();
	auto sy = y() + Fl::box_dx(box()) + Fl::box_dx(_area->box()) + _margin.top - _vscroll->value();

	for (auto item : _items)
	{
		if (item->widget == nullptr) {
			continue;
		}

		int ypos = sy;
		int height = 0;
		for (int i = 0; i <= item->row.end; i++)
		{
			if (i < item->row.start) {
				const auto pRow = _rows[i].get();
				ypos += pRow->height + pRow->gap;
				continue;
			}

			const auto pRow = _rows[i].get();
			height += pRow->height;
			if (i < item->row.end) {
				height += pRow->gap;
			}
		}

		;
		int xpos = sx;
		int width = 0;
		for (int i = 0; i <= item->column.end; i++)
		{
			if (i < item->column.start) {
				const auto pCol = _columns[i].get();
				xpos += pCol->width + pCol->gap;
				continue;
			}

			const auto pCol = _columns[i].get();
			width += pCol->width;
			if (i < item->column.end) {
				width += pCol->gap;
			}
		}

		item->widget->resize(xpos, ypos, width, height);
	}


	OnGridResized();
}

void Grid::RecalcArea()
{
	_areax = x() + Fl::box_dx(box()) + Fl::box_dx(_area->box()) + _margin.left;
	_areay = y() + Fl::box_dx(box()) + Fl::box_dx(_area->box()) + _margin.top;
	_areaw = w() - Fl::box_dx(box()) - Fl::box_dx(_area->box()) - _margin.left - _margin.right;
	_areah = h() - Fl::box_dx(box()) - Fl::box_dx(_area->box()) - _margin.top - _margin.bottom;

	auto vhide = _areaVirtH <= _areah;
	auto hhide = _areaVirtW <= _areaw;
	auto scrollsize = Fl::scrollbar_size();

	if (!hhide && vhide) {
		vhide = ((_areaVirtH - _areah + scrollsize) <= 0);
	}

	if (!vhide && hhide) {
		hhide = ((_areaVirtW - _areaw + scrollsize) <= 0);
	}

	if (vhide) {
		_vscroll->hide();
	}
	else {
		_vscroll->show();
		_areaw -= scrollsize;
	}

	if (hhide) {
		_hscroll->hide();
	}
	else {
		_hscroll->show();
		_areah -= scrollsize;
	}

	_area->resize(_areax, _areay, _areaw, _areah);
	_area->init_sizes();
}

void Grid::RecalcRowsOffsets()
{
	int voffs = _vscroll->value();
	int py = 0;
	int row = 0;

	for (; row < _rows.size(); row++) {
		const auto pRow = _rows[row].get();
		auto height = pRow->height + pRow->gap;
		py += height;
		if (py > voffs) {
			py -= height;
			break;
		}
	}

	_rowPosition = _topRow = row;
	_topRowScrollpos = py;

	voffs = _vscroll->value() + _areah;

	for (; row < _rows.size(); row++) {
		const auto pRow = _rows[row].get();
		auto height = pRow->height + pRow->gap;
		py += height;
		if (py >= voffs) {
			break;
		}
	}

	_bottomRow = row;
}

void Grid::RecalcColumnsOffsets()
{
	int hoffs = _hscroll->value();
	int px = 0;
	int col = 0;

	for (; col < _columns.size(); col++) {
		const auto pCol = _columns[col].get();
		auto width = pCol->width + pCol->gap;
		px += width;
		if (px > hoffs) {
			px -= width;
			break;
		}
	}

	_colPosition = _leftCol = col;
	_leftColScrollpos = px;

	hoffs = _vscroll->value() + _areaw;

	for (; col < _columns.size(); col++) {
		const auto pCol = _columns[col].get();
		auto width = pCol->width + pCol->gap;
		px += width;
		if (px >= hoffs) {
			break;
		}
	}

	_rightCol = col;
}

void Grid::OnGridScrilled()
{
	RecalcRowsOffsets();
	RecalcColumnsOffsets();
}

long Grid::GetRowScrollPos(int row)
{
	int startrow = 0;
	long scroll = 0;

	if (_topRowScrollpos != -1 && row >= _topRow) {
		scroll = _topRowScrollpos;
		startrow = _topRow;
	}

	for (int i = startrow; i < row; i++) {
		const auto pRow = _rows[i].get();
		scroll += pRow->height + pRow->gap;
	}

	return scroll;
}

long Grid::GetColumnScrollPos(int column)
{
	int startcol = 0;
	long scroll = 0;

	if (_leftColScrollpos != -1 && column >= _leftCol) {
		scroll = _leftColScrollpos;
		startcol = _leftCol;
	}

	for (int i = startcol; i < column; i++) {
		const auto pCol = _columns[i].get();
		scroll += pCol->width + pCol->gap;
	}

	return scroll;
}

void Grid::OnGridResized()
{
	_areaVirtH = GetRowScrollPos(_rows.size());
	_areaVirtW = GetColumnScrollPos(_columns.size());

	RecalcArea();

	float vtab = (_areaVirtH == 0 || _areah > _areaVirtH) ? 1 : (float)_areah / _areaVirtH;
	float htab = (_areaVirtW == 0 || _areaw > _areaVirtW) ? 1 : (float)_areaw / _areaVirtW;

	auto sx = x() + Fl::box_dx(box());
	auto sy = y() + Fl::box_dx(box());
	auto sw = w() - Fl::box_dx(box());
	auto sh = h() - Fl::box_dx(box());

	_vscroll->resize(sx + sw - Fl::scrollbar_size(), sy,
		Fl::scrollbar_size(), sh - Fl::scrollbar_size());
	_vscroll->bounds(0, _areaVirtH - _areah);
	_vscroll->precision(10);
	_vscroll->slider_size(vtab);
	_vscroll->Fl_Valuator::value(_vscroll->clamp(_vscroll->value()));

	_hscroll->resize(sx, sy + sh - Fl::scrollbar_size(),
		sw, Fl::scrollbar_size());
	_hscroll->bounds(0, _areaVirtW - _areaw);
	_hscroll->precision(10);
	_hscroll->slider_size(htab);
	_hscroll->Fl_Valuator::value(_hscroll->clamp(_hscroll->value()));

	Fl_Group::init_sizes();

	OnGridScrilled();
}

void Grid::end()
{
	_area->end();

	if (_area->children() > 2) {
		_area->show();
	}
	else {
		_area->hide();
	}

	Container::end();
}

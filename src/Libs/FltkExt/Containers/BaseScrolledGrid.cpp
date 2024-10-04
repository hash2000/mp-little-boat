#include "BaseScrolledGrid.h"

BaseScrolledGrid::BaseScrolledGrid(int cx, int cy, int cw, int ch)
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

	Container::end();

	_area->begin();
}

const Margin& BaseScrolledGrid::margin() const
{
	return _margin;
}

void BaseScrolledGrid::margin(const Margin& m)
{
	_margin = m;
	RecalcLayout();
}

const Fl_Scroll* const BaseScrolledGrid::GetArea() const
{
	return _area.get();
}

const Fl_Scrollbar* const BaseScrolledGrid::GetVScroll() const
{
	return _vscroll.get();
}

const Fl_Scrollbar* const BaseScrolledGrid::GetHScroll() const
{
	return _hscroll.get();
}

void BaseScrolledGrid::begin()
{
	_area->begin();
}

void BaseScrolledGrid::end()
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

Fl_Widget* const* BaseScrolledGrid::array()
{
	return _area->array();
}

Fl_Widget* BaseScrolledGrid::child(int n) const
{
	return _area->child(n);
}

int BaseScrolledGrid::children() const
{
	// -2: skip Fl_Scroll's h/v scrollbar widgets
	return _area->children() - 2;  
}

int BaseScrolledGrid::find(const Fl_Widget* wgt) const
{
	return _area->find(wgt);
}

int BaseScrolledGrid::find(const Fl_Widget& wgt) const
{
	return _area->find(wgt);
}

void BaseScrolledGrid::init_sizes() {
	_area->init_sizes();
	_area->redraw();
}

void BaseScrolledGrid::OnScroll(Fl_Widget* widget, void* data)
{
	auto me = (BaseScrolledGrid*)data;
	me->RecalcArea();
	me->GridScrilled();
	me->RecalcLayout();
	me->redraw();
}

int BaseScrolledGrid::GetClientAreaX() const
{
	return _areax;
}

int BaseScrolledGrid::GetClientAreaY() const
{
	return _areay;
}

int BaseScrolledGrid::GetClientAreaW() const
{
	return _areaw;
}

int BaseScrolledGrid::GetClientAreaH() const
{
	return _areah;
}

void BaseScrolledGrid::RecalcArea()
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

void BaseScrolledGrid::RecalcRowsOffsets()
{
	int rows = GetRowsCount();
	int voffs = _vscroll->value();
	int py = 0;
	int row = 0;

	for (; row < rows; row++) {
		auto height = GetRowHeight(row);
		py += height;
		if (py > voffs) {
			py -= height;
			break;
		}
	}

	_rowPosition = _topRow = row;
	_topRowScrollpos = py;

	voffs = _vscroll->value() + _areah;

	for (; row < rows; row++) {
		auto height = GetRowHeight(row);
		py += height;
		if (py >= voffs) {
			break;
		}
	}

	_bottomRow = row;
}

void BaseScrolledGrid::RecalcColumnsOffsets()
{
	int cols = GetColumnsCount();
	int hoffs = _hscroll->value();
	int px = 0;
	int col = 0;

	for (; col < cols; col++) {
		auto width = GetColumnWidth(col);
		px += width;
		if (px > hoffs) {
			px -= width;
			break;
		}
	}

	_colPosition = _leftCol = col;
	_leftColScrollpos = px;

	hoffs = _vscroll->value() + _areaw;

	for (; col < cols; col++) {
		auto width = GetColumnWidth(col);
		px += width;
		if (px >= hoffs) {
			break;
		}
	}

	_rightCol = col;
}


void BaseScrolledGrid::GridScrilled()
{
	RecalcRowsOffsets();
	RecalcColumnsOffsets();
}

long BaseScrolledGrid::GetRowScrollPos(int row)
{
	int startrow = 0;
	long scroll = 0;

	if (_topRowScrollpos != -1 && row >= _topRow) {
		scroll = _topRowScrollpos;
		startrow = _topRow;
	}

	for (int i = startrow; i < row; i++) {
		scroll += GetRowHeight(i);;
	}

	return scroll;
}

long BaseScrolledGrid::GetColumnScrollPos(int column)
{
	int startcol = 0;
	long scroll = 0;

	if (_leftColScrollpos != -1 && column >= _leftCol) {
		scroll = _leftColScrollpos;
		startcol = _leftCol;
	}

	for (int i = startcol; i < column; i++) {
		scroll += GetColumnWidth(i);
	}

	return scroll;
}

void BaseScrolledGrid::GridResized()
{
	_areaVirtH = GetRowScrollPos(GetRowsCount());
	_areaVirtW = GetColumnScrollPos(GetColumnsCount());

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

	GridScrilled();
}

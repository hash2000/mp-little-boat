#include "Grid.h"
#include <FL/fl_draw.H>
#include <algorithm>

Grid::Grid(int cx, int cy, int cw, int ch)
	: BaseScrolledGrid(cx, cy, cw, ch)
{
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

void Grid::AddWidget(Fl_Widget* widget, int row, int column, Alignment::Type align)
{
	AddWidget(widget,
		GridPosition{ .start = row, .end = row },
		GridPosition{ .start = column, .end = column },
		align);
}

void Grid::AddWidget(Fl_Widget* widget,
	const GridPosition& row,
	const GridPosition& column,
	Alignment::Type align)
{
	auto child = GetArea()->find(widget);
	if (child >= GetArea()->children()) {
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
	pWidget->align = align;

	_items.push_back(pWidget);

	RecalcLayout();
}

int Grid::GetRowsCount() const
{
	return _rows.size();
}

int Grid::GetColumnsCount() const
{
	return _columns.size();
}

int Grid::GetRowHeight(int row) const
{
	const auto pRow = _rows[row].get();
	return pRow->height + pRow->gap;
}

int Grid::GetColumnWidth(int columns) const
{
	const auto pCol = _columns[columns].get();
	return pCol->width + pCol->gap;
}


void Grid::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::AdjustLayout(cx, cy, cw, ch);

	RecalcArea();

	if (_rows.size() == 0 || _columns.size() == 0) {
		return;
	}

	auto sx = x() + Fl::box_dx(box()) + Fl::box_dx(GetArea()->box()) + margin().left - GetHScroll()->value();
	auto sy = y() + Fl::box_dx(box()) + Fl::box_dx(GetArea()->box()) + margin().top - GetVScroll()->value();

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

		Alignment::Type align = item->align;
		Alignment::Type mask = Alignment::Left | Alignment::Right | Alignment::Horizontal | Alignment::Center;

		if (item->widget->w() == 0 || item->widget->h() == 0) {
			align = Alignment::Fill;
		}


		if ((align & mask) == Alignment::Center) {
			xpos += (width - item->widget->w()) / 2;
			width = item->widget->w();
		}
		else if ((align & mask) == Alignment::Left) {
			width = item->widget->w();
		}
		else if ((align & mask) == Alignment::Right) {
			xpos += width - item->widget->w();
			width = item->widget->w();
		}

		mask = Alignment::Top | Alignment::Bottom | Alignment::Vertical | Alignment::Center;

		if ((align & mask) == Alignment::Center) {
			ypos += (height - item->widget->h()) / 2;
			height = item->widget->h();
		}
		else if ((align & mask) == Alignment::Top) {
			height = item->widget->h();
		}
		else if ((align & mask) == Alignment::Bottom) {
			ypos += height - item->widget->h();
			height = item->widget->h();
		}

		item->widget->resize(xpos, ypos, width, height);
	}

	GridResized();
}


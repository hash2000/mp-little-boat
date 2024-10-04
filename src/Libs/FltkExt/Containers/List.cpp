#include "List.h"

namespace FltkExt::Containers
{


	List::List(int cx, int cy, int cw, int ch, Direction direction)
		: BaseScrolledGrid(cx, cy, cw, ch)
		, _direction(direction)
	{
	}

	int List::GetRowsCount() const
	{
		return _direction == Direction::Vert ? children() : 1;
	}

	int List::GetColumnsCount() const
	{
		return _direction == Direction::Horz ? children() : 1;
	}

	int List::gap() const
	{
		return _gap;
	}

	void List::gap(int size)
	{
		_gap = size;
		RecalcLayout();
	}

	int List::GetRowHeight(int row) const
	{
		if (_direction == Direction::Horz) {
			return 1;
		}

		if (row >= children()) {
			return 0;
		}

		auto widget = child(row);

		return widget->h() + _gap;
	}

	int List::GetColumnWidth(int columns) const
	{
		if (_direction == Direction::Vert) {
			return 1;
		}

		if (columns >= children()) {
			return 0;
		}

		auto widget = child(columns);

		return widget->w() + _gap;
	}

	void List::AdjustLayout(int cx, int cy, int cw, int ch)
	{
		BaseScrolledGrid::AdjustLayout(cx, cy, cw, ch);
		RecalcArea();

		auto sx = GetClientAreaX() - GetHScroll()->value();
		auto sy = GetClientAreaY() - GetVScroll()->value();
		auto sw = GetClientAreaW();
		auto sh = GetClientAreaH();
		const int nc = children();

		for (int i = 0; i < nc; i++)
		{
			auto c = child(i);
			auto pw = _direction == Direction::Horz ? c->w() : sw;
			auto ph = _direction == Direction::Horz ? sh : c->h();

			c->resize(sx, sy, pw, ph);

			if (_direction == Direction::Horz) {
				sx += pw + _gap;
			}
			else {
				sy += ph + _gap;
			}
		}

		GridResized();
	}

}

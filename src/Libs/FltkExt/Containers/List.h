#pragma once
#include <FL/Fl.H>
#include "Libs/FltkExt/Containers/BaseScrolledGrid.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"

class List : public BaseScrolledGrid
{
public:
	List(int cx, int cy, int cw, int ch, Direction direction = Direction::Horz);

	int GetRowsCount() const override;

	int GetColumnsCount() const override;

	int GetRowHeight(int row) const override;

	int GetColumnWidth(int columns) const override;

	int gap() const;

	void gap(int size);

private:

	void AdjustLayout(int cx, int cy, int cw, int ch) override;

private:

	Direction _direction;
	int _gap = 0;
};

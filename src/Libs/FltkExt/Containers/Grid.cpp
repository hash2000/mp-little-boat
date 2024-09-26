#include "Grid.h"

Grid::Grid(int cx, int cy, int cw, int ch, int rows, int columns)
	: Container(cx, cy, cw, ch)
	, _rows(rows)
	, _columns(columns)
{
}

void Grid::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Container::AdjustLayout(cx, cy, cw, ch);



}

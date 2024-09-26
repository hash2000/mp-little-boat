#pragma once
#include "Libs/FltkExt/Containers/Container.h"

class Grid : public Container
{
public:
	Grid(int cx, int cy, int cw, int ch, int rows, int columns);

private:
	void AdjustLayout(int cx, int cy, int cw, int ch) override;

private:
	int _rows;
	int _columns;
};

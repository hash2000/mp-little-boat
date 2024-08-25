#pragma once
#include <FL/Fl_Group.H>
#include "Navigator/Controls/Containers/Margin.h"

class Flex : public Fl_Group
{
public:
	enum class Direction {
		Vert,
		Horz,
	};

	enum class Position {
		Start,
		End,
		Center
	};

	Flex(Direction direction, Position pos, int size = -1, const Margin& margin = Margin());

	void AdjustLayout();

	void resize(int cx, int cy, int cw, int ch);

private:
	Direction _direction;
	Position _position;
	Margin _margin;
	int _size;
	int _gap = 0;
};

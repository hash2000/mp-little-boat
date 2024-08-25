#pragma once

#include <string>
#include <FL/Fl_Group.H>

enum class ToolbarPosition {
	Left,
	Right,
	Top,
	Bottom,
};

class Toolbar : public Fl_Group
{
public:
	Toolbar(ToolbarPosition position, int size);

	void resize(int cx, int cy, int cw, int ch);

	void AdjusSizes();

private:
	int _size;
	ToolbarPosition _position;
};

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
	Toolbar(ToolbarPosition position);

	void resize(int x, int y, int cw, int ch);

	void draw();

	void end();

protected:
	ToolbarPosition _position;
	Fl_Group _spacer;
};

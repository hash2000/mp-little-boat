#pragma once

#include <string>
#include <FL/Fl_Group.H>

class Toolbar : public Fl_Group
{
public:
	Toolbar(int x, int y, int cw, int ch, const char* title = nullptr);

	void resize(int x, int y, int cw, int ch);

	void draw();

	void end();

protected:

	Fl_Group _spacer;
};

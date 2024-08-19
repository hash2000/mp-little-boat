#pragma once

#include <string>
#include <FL/Fl_Group.H>

class Toolbar : public Fl_Group
{
public:
	Toolbar(int x, int y, int w, int h, const char* title = nullptr);

	void resize(int x, int y, int w, int h);

	void draw();

	void end();

protected:

	Fl_Group _spacer;
};

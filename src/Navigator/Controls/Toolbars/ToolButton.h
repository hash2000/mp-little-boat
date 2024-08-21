#pragma once

#include <string>
#include <FL/Fl_Button.H>

class ToolButton : public Fl_Button
{
public:
	ToolButton(int x, int y, int cw, int ch, const char* title = nullptr);

protected:
	void draw(void);
	int handle(int event);
};

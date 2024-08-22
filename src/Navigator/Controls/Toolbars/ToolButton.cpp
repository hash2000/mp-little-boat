#include <pch.h>
#include "ToolButton.h"

ToolButton::ToolButton(int x, int y, int cw, int ch, const char* title)
	: Fl_Button(x, y, cw, ch, title)
{
	box(FL_FREE_BOXTYPE);
	color(FL_BACKGROUND_COLOR);
	down_box(FL_GLEAM_DOWN_BOX);
	down_color(FL_SELECTION_COLOR);
	labelfont(FL_FREE_FONT);
	labelsize(12);
	align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
}

void ToolButton::draw(void)
{
	//auto v = value();
	//Fl_Color col = v ? fl_lighter(color()) : color();
	//draw_box(v ? down_box() : box(), col);
	//draw_backdrop();
	//if (labeltype() == FL_NORMAL_LABEL && v) {
	//	Fl_Color c = labelcolor();
	//	labelcolor(fl_contrast(c, col));
	//	draw_label();
	//	labelcolor(c);
	//}
	//else {
	//	draw_label();
	//}
	//if (Fl::focus() == this) {
	//	draw_focus();
	//}
	Fl_Button::draw();
}

int ToolButton::handle(int event)
{
	//switch (event) {
	//case FL_ENTER:
	//	if (active_r()) {
	//		color(FL_LIGHT3);
	//		box(FL_GLEAM_ROUND_UP_BOX);
	//		redraw();
	//		return 1;
	//	}
	//	return 0;
	//case FL_LEAVE:
	//	color(FL_BACKGROUND_COLOR);
	//	box(FL_FREE_BOXTYPE);
	//	redraw();
	//	return 1;
	//case FL_PUSH:
	//	Fl::focus(this);
	//}
	return Fl_Button::handle(event);
}

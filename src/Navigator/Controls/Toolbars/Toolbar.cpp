#include <pch.h>
#include "Toolbar.h"


Toolbar::Toolbar(int x, int y, int w, int h, const char* title)
	: Fl_Group(x, y, w, h, title)
	, _spacer(0, 0, 0, 0)
{
	labeltype(FL_NO_LABEL);
	box(FL_FREE_BOXTYPE);
	resizable(_spacer);
	clip_children(1);
	begin();
}

void Toolbar::resize(int x, int y, int w, int h)
{
	add(_spacer);
	resizable(_spacer);
	Fl_Group::resize(x, y, w, h);
}

void Toolbar::draw()
{
	int tx = x() + Fl::box_dx(box()), ty = y() + Fl::box_dy(box());
	int tw = w() - Fl::box_dw(box()), th = h() - Fl::box_dh(box());
	int cur_x = tx, max_x = tx;
	uchar d = damage();
	Fl_Widget* const* a = array();
	int rw = 0;
	for (int i = children(); i--;) {
		if (child(i)->visible()) {
			if (child(i) != this->resizable()) { rw += child(i)->w(); }
		}
	}
	for (int i = children(); i--;) {
		Fl_Widget* o = *a++;
		if (!o->visible()) { continue; }
		int X = cur_x, Y = ty + (th - o->h()) / 2, W = o->w();
		if (i == 0 && o == this->resizable()) { W = tw - rw; } // last child, if resizable, takes all remaining room
		if (X != o->x() || Y != o->y() || W != o->w()) {
			o->resize(X, Y, W, o->h());
			o->clear_damage(FL_DAMAGE_ALL);
		}
		if (d & FL_DAMAGE_ALL) {
			draw_child(*o);
			draw_outside_label(*o);
		}
		else {
			update_child(*o);
		}
		cur_x += o->w(); // child's draw() can change it's size, so use new size
		if (cur_x > max_x) { max_x = cur_x; }
	}
	if (max_x < tx + tw && box()) {
		fl_color(color());
		fl_rectf(max_x, ty, tx + tw - max_x, th);
	}
	tw = max_x - tx;
	tw += Fl::box_dw(box()); if (tw <= 0) { tw = 1; }
	th += Fl::box_dh(box()); if (th <= 0) { th = 1; }
	if (tw != w() || th != h()) {
		Fl_Widget::resize(x(), y(), tw, th);
		d = FL_DAMAGE_ALL;
	}
	if (d & FL_DAMAGE_ALL) {
		draw_box();
		draw_label();
	}
}

void Toolbar::end()
{
	resize(x(), y(), w(), h());
}
#include "Container.h"

Container::Container(int cx, int cy, int cw, int ch)
	: Fl_Group(cx, cy, cw, ch, nullptr)
{
	set_flag(CLIP_CHILDREN);
	begin();
}

void Container::RecalcLayout(bool set)
{
	_needRecalculate = set;
}

void Container::resize(int cx, int cy, int cw, int ch)
{
	AdjustLayout(cx, cy, cw, ch);
}

void Container::AdjustLayout(int cx, int cy, int cw, int ch)
{
	// Контейнер не должен делать ресайз дочерних компонентов,
	// поэтому тут не Fl_Widget::resize
	Fl_Widget::resize(cx, cy, cw, ch);
}

void Container::draw()
{
	if (_needRecalculate) {
		_needRecalculate = false;
		AdjustLayout(x(), y(), w(), h());
	}

	Fl_Group::draw();
}

void Container::end()
{
	Fl_Group::end();
	RecalcLayout();
}

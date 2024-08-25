#include <pch.h>
#include "Toolbar.h"
#include "ToolButton.h"


Toolbar::Toolbar(ToolbarPosition position, int size)
	: Fl_Group(0, 0, 0, 0, nullptr)
	, _size(size)
	, _position(position)
{
	resizable(this);
	labeltype(FL_NO_LABEL);
	box(FL_GTK_DOWN_BOX);
	clip_children(1);
	align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	AdjusSizes();
}

void Toolbar::resize(int cx, int cy, int cw, int ch)
{
	Fl_Group::resize(cx, cy, cw, ch);
	AdjusSizes();
}

void Toolbar::AdjusSizes()
{
	auto p = parent();
	if (_position == ToolbarPosition::Bottom) {
		w(p->w());
		h(_size);
	}
	else if (_position == ToolbarPosition::Top) {
		w(p->w());
		y(p->h() - _size);
		h(_size);
	}
	else if (_position == ToolbarPosition::Right) {
		w(_size);
		h(p->h());
		x(p->w() - _size);
	}
	else if (_position == ToolbarPosition::Left) {
		w(_size);
		h(p->h());
	}
}


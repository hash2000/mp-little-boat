#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include "Libs/FltkExt/Containers/ContainerProps.h"

class Splitter : public Fl_Box
{
public:
	Splitter(int cx, int cy, int cw, int ch, Direction direction = Direction::Horz);

	void resizable(Fl_Widget* widget);

	void resizable(Fl_Widget& widget);

	Fl_Widget* resizable() const;

	Direction direction() const;

	void direction(Direction dir);

	PushPosition GetPushPosition() const;

	void SetPushPosition(PushPosition pos);

protected:

	int handle(int event) override;

	bool IsEventInside() const;

	void ChangeCursor(Fl_Cursor newcursor);

private:

	Fl_Widget* _resizable;
	Fl_Cursor _lastCursor = FL_CURSOR_DEFAULT;
	Direction _direction;
	PushPosition _pushPosition;
	int _resize_start;

};

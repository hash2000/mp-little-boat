#pragma once

class Margin
{
public:
	Margin() {
	}

	Margin(int size)
		: _left(size)
		, _top(size)
		, _right(size)
		, _bottom(size)
	{
	}

	Margin(int l, int t, int r, int b)
		: _left(l)
		, _top(t)
		, _right(r)
		, _bottom(b)
	{
	}

	Margin& operator = (const Margin& p) {
		_left = p._left;
		_top = p._top;
		_right = p._right;
		_bottom = p._bottom;
		return *this;
	}

public:
	int _left = 0;
	int _right = 0;
	int _top = 0;
	int _bottom = 0;
};

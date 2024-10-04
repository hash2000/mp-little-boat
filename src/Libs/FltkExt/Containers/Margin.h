#pragma once

namespace FltkExt::Containers
{

	class Margin
	{
	public:
		Margin()
			: left(0)
			, top(0)
			, right(0)
			, bottom(0)
		{
		}

		Margin(int size)
			: left(size)
			, top(size)
			, right(size)
			, bottom(size)
		{
		}

		Margin(int l, int t, int r, int b)
			: left(l)
			, top(t)
			, right(r)
			, bottom(b)
		{
		}

		Margin& operator = (const Margin& r) {
			left = r.left;
			top = r.top;
			right = r.right;
			bottom = r.bottom;
			return *this;
		}

	public:
		int left;
		int top;
		int right;
		int bottom;
	};

}

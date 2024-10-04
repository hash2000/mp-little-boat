#include "Flex.h"
#include <FL/Fl_Widget.H>
#include <algorithm>

namespace FltkExt::Containers
{

	Flex::Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position)
		: Container(cx, cy, cw, ch)
		, _gap(0)
		, _direction(direction)
		, _position(position)
		, _layoutStraategy(LayoutStrategy::ByDirection)
	{
		_size = _direction == Direction::Horz ? ch : cw;
		type((int)direction);
		begin();
	}

	void Flex::AdjustLayout(int cx, int cy, int cw, int ch)
	{
		BeginLayout();
		AdjustMainSizes(cx, cy, cw, ch);

		const int nc = children();
		int fcount = 0;
		int fspace = 0;

		// Calculate inner control fixed sizes space
		for (int i = 0; i < nc; i++)
		{
			Fl_Widget* c = child(i);
			if (!c->visible()) {
				continue;
			}

			auto el = _elements[i];
			auto sz = _direction == Direction::Horz ? el->width : el->height;
			if (el->useBounds && sz > 0) {
				fspace += sz;
				fcount++;
			}
		}

		auto sx = x() + Fl::box_dx(box()) + _margin.left;
		auto sy = y() + Fl::box_dx(box()) + _margin.top;
		auto sw = w() - Fl::box_dx(box()) - _margin.left - _margin.right;
		auto sh = h() - Fl::box_dx(box()) - _margin.top - _margin.bottom;

		auto fixedSize = _size - (_direction == Direction::Horz ?
			_margin.top + _margin.bottom : _margin.left + _margin.right);

		auto ncsize = nc > 1 ? (nc - 1) * _gap : 0;
		auto cstart = _direction == Direction::Horz ? sx : sy;
		auto csize = _direction == Direction::Horz ? sw : sh;

		auto nfcount = nc - fcount;
		auto ctlsize = 0;

		if (nfcount > 0) {
			ctlsize = csize - fspace - ncsize;
			ctlsize /= nfcount;
		}

		auto directionSize = _direction == Direction::Horz ? sh : sw;
		auto dockingSize = _layoutStraategy == LayoutStrategy::ByDirection ? fixedSize : directionSize;

		if (_position == PushPosition::Start)
		{
			for (int i = 0; i < nc; i++)
			{
				Fl_Widget* c = child(i);
				if (!c->visible()) {
					continue;
				}

				auto useBounds = _elements[i]->useBounds;
				auto size = _direction == Direction::Horz ?
					_elements[i]->width :
					_elements[i]->height;
				size = useBounds && size > 0 ? size : ctlsize;

				auto px = _direction == Direction::Horz ? cstart : sx;
				auto py = _direction == Direction::Horz ? sy : cstart;
				auto pw = _direction == Direction::Horz ? size : dockingSize;
				auto ph = _direction == Direction::Horz ? dockingSize : size;

				c->resize(px, py, pw, ph);
				size = _direction == Direction::Horz ? c->w() : c->h();

				cstart += size + _gap;
			}
		}
		else if (_position == PushPosition::End)
		{
			auto pstart = _direction == Direction::Horz ? sw : sh;
			for (int i = 0; i < nc; i++)
			{
				Fl_Widget* c = child(i);
				if (!c->visible()) {
					continue;
				}

				auto useBounds = _elements[i]->useBounds;
				auto size = _direction == Direction::Horz ?
					_elements[i]->width :
					_elements[i]->height;
				size = useBounds && size > 0 ? size : ctlsize;

				auto pw = _direction == Direction::Horz ? size : dockingSize;
				auto ph = _direction == Direction::Horz ? dockingSize : size;
				auto px = _direction == Direction::Horz ? pstart - pw - _gap + sx : sx;
				auto py = _direction == Direction::Horz ? sy : pstart - ph - _gap + sy;

				c->resize(px, py, pw, ph);
				size = _direction == Direction::Horz ? c->w() : c->h();

				pstart -= size + _gap;
			}
		}

		EndLayout();
	}

	bool Flex::InitElementsContent()
	{
		const int nc = children();
		bool result = false;

		if (_elements.size() != nc || !_elementsInitialized)
		{
			result = true;
			_elementsInitialized = true;
			_elements.resize(nc);
			for (int i = 0; i < nc; i++)
			{
				if (!_elements[i]) {
					_elements[i] = std::make_shared<ElementContext>();
				}
			}
		}

		return result;
	}

	void Flex::BeginLayout()
	{
		if (!InitElementsContent()) {
			return;
		}

		const int nc = children();

		for (int i = 0; i < nc; i++)
		{
			Fl_Widget* c = child(i);
			auto pw = c->w();
			auto ph = c->h();

			Flex* flex = dynamic_cast<Flex*>(c);
			if (flex != nullptr)
			{
				if (flex->GetLayoutStrategy() == LayoutStrategy::Full) {
					pw = 0;
					ph = 0;
				}
			}

			auto el = _elements[i];
			el->width = pw;
			el->height = ph;
		}
	}

	void Flex::UseBounds(const Fl_Widget* widget, bool set)
	{
		InitElementsContent();

		const int nc = children();

		for (int i = 0; i < nc; i++)
		{
			auto pc = child(i);
			if (pc == widget) {
				_elements[i]->useBounds = set;
				break;
			}
		}
	}

	void Flex::EndLayout()
	{
		redraw();
	}

	void Flex::on_remove(int index)
	{
		int idx = 0;
		for (auto i = _elements.begin(); i != _elements.end(); i++)
		{
			if (idx == index) {
				_elements.erase(i);
				return;
			}
		}

		RecalcLayout();
	}

	void Flex::AdjustMainSizes(int cx, int cy, int cw, int ch)
	{
		if (_layoutStraategy == LayoutStrategy::ByDirection)
		{
			if (_direction == Direction::Horz)
			{
				Fl_Widget::resize(cx, cy, cw, _size);
			}
			else
			{
				Fl_Widget::resize(cx, cy, _size, ch);
			}
		}
		else if (_layoutStraategy == LayoutStrategy::ByDirectionReflected)
		{
			if (_direction == Direction::Horz)
			{
				Fl_Widget::resize(cx, parent()->h() - _size, cw, _size);
			}
			else
			{
				Fl_Widget::resize(parent()->w() - _size, cy, _size, ch);
			}
		}
		else if (_layoutStraategy == LayoutStrategy::Full)
		{

			Fl_Widget::resize(cx, cy, cw, ch);
		}
	}

	int Flex::gap() const
	{
		return _gap;
	}

	void Flex::gap(int size)
	{
		_gap = size;
	}

	PushPosition Flex::GetPushPosition() const
	{
		return _position;
	}

	void Flex::SetPushPosition(PushPosition pos)
	{
		_position = pos;
		RecalcLayout();
	}

	Direction Flex::direction() const
	{
		return _direction;
	}

	void Flex::direction(Direction dir)
	{
		_direction = dir;
		RecalcLayout();
	}

	LayoutStrategy Flex::GetLayoutStrategy() const
	{
		return _layoutStraategy;
	}

	void Flex::SetLayoutStrategy(LayoutStrategy set)
	{
		_layoutStraategy = set;
		RecalcLayout();
	}

	const Margin& Flex::margin() const
	{
		return _margin;
	}

	void  Flex::margin(const Margin& m)
	{
		_margin = m;
		RecalcLayout();
	}

}

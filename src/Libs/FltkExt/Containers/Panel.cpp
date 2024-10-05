#include "Panel.h"
#include "Flex.h"
#include "Splitter.h"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Button.H>

namespace FltkExt::Containers
{


	Panel::Panel(int size, const char* l)
		: Container(0, 0, size, size)
	{
		box(FL_FREE_BOXTYPE);

		auto headerColor = fl_lighter(FL_BLUE);
		auto headerTextColor = fl_lighter(FL_WHITE);
		auto headerSize = 20;
		auto parentWidget = parent();

		_topFlex = std::make_unique<Flex>(0, 0, w(), h(), Direction::Vert);
		_topFlex->box(FL_FREE_BOXTYPE);
		_topFlex->SetLayoutStrategy(LayoutStrategy::Full);
		{
			_topContentFlex = std::make_unique<Flex>(0, 0, 0, 0, Direction::Vert);
			_topContentFlex->SetLayoutStrategy(LayoutStrategy::Full);
			_topContentFlex->margin(Margin(1));
			{
				_topHeaderFlex = std::make_unique<Flex>(0, 0, w(), headerSize, Direction::Horz, PushPosition::End);
				_topHeaderFlex->box(FL_FLAT_BOX);
				_topHeaderFlex->color(headerColor);
				_topHeaderFlex->label(l);
				_topHeaderFlex->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
				_topHeaderFlex->labelcolor(headerTextColor);
				{
					_hideButton = std::make_unique<Fl_Button>(0, 0, headerSize, headerSize);
					_hideButton->color(headerColor);
					_hideButton->box(FL_ENGRAVED_BOX);

					_pinButton = std::make_unique<Fl_Button>(0, 0, headerSize, headerSize);
					_pinButton->color(headerColor);
					_pinButton->box(FL_ENGRAVED_BOX);

					_topHeaderFlex->end();
				}

				_topContentFlex->end();
			}

			_splitter = std::make_unique<Splitter>(10, Direction::Vert);
			_splitter->box(FL_ENGRAVED_BOX);
			_splitter->resizable(this);

			_topFlex->end();
		}

		_topContentFlex->begin();
	}

	void Panel::UseHeader(bool use)
	{
		if (use) {
			_topHeaderFlex->show();
		}
		else {
			_topHeaderFlex->hide();
		}
	}

	void Panel::UseSplitter(bool use)
	{
		if (use) {
			_splitter->show();
		}
		else {
			_splitter->hide();
		}
	}

	void Panel::SetMinPanelSize(int size)
	{
		_minPanelSize = size;
	}

	int Panel::GetMinPanelSize() const
	{
		return _minPanelSize;
	}

	void Panel::AdjustLayout(int cx, int cy, int cw, int ch)
	{
		Container::AdjustLayout(cx, cy, cw, ch);

		if (_topFlex) {
			_topFlex->resize(cx, cy, cw, ch);
		}
	}

	void Panel::UpdateDockingState(Docking docking)
	{
		_docking = docking;
		if (docking == Docking::Center) {
			_splitter->hide();
			return;
		}
		else {
			_splitter->show();
		}

		auto direction = docking == Docking::Left || docking == Docking::Right ?
			Direction::Horz : Direction::Vert;
		auto pos = docking == Docking::Left || docking == Docking::Top ?
			PushPosition::Start : PushPosition::End;

		_topFlex->direction(direction);
		_topFlex->SetPushPosition(pos);

		_splitter->direction(direction);
		_splitter->SetPushPosition(pos);
	}

	Docking Panel::GetDockingState() const
	{
		return _docking;
	}

	void Panel::begin()
	{
		_topContentFlex->begin();
	}

	void Panel::end()
	{
		_topContentFlex->end();
		Container::end();
	}

	void Panel::UseBounds(const Fl_Widget* widget, bool set)
	{
		_topContentFlex->UseBounds(widget, set);
	}

	Fl_Widget* const* Panel::array()
	{
		return _topContentFlex->array();
	}

	Fl_Widget* Panel::child(int n) const
	{
		return _topContentFlex->child(n);
	}

	int Panel::children() const
	{
		return _topContentFlex->children();
	}

	int Panel::find(const Fl_Widget* wgt) const
	{
		return _topContentFlex->find(wgt);
	}

	int Panel::find(const Fl_Widget& wgt) const
	{
		return _topContentFlex->find(wgt);
	}

	void Panel::init_sizes()
	{
		_topContentFlex->init_sizes();
		_topContentFlex->redraw();
	}



}

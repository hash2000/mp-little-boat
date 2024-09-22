#include "Layout.h"
#include "Panel.h"

Layout::Layout(int cx, int cy, int cw, int ch)
	: Container(cx, cy, cw, ch)
{
}

void Layout::Attach(Panel& p, Docking docking)
{
	//	auto found = find((const Fl_Widget&)p);

	if (docking == Docking::Center)
	{
		if (_centerPanel)
		{
			std::printf("*** Layout: Center widget allready added");
			return;
		}

		_centerPanel = &p;
		_centerPanel->UpdateDockingState(docking);
		return;
	}

	for (auto dock : _panelDocking) {
		for (auto panelIt = dock.second.begin(); panelIt != dock.second.end(); panelIt++) {
			auto panel = *panelIt;
			if (panel == &p) {
				if (dock.first == docking) {
					// уже добавлена с таким же расположением как указано
					return;
				}
				else {
					dock.second.erase(panelIt);
				}
			}
		}
	}

	auto dockIt = _panelDocking.find(docking);
	if (dockIt == _panelDocking.end()) {
		dockIt = _panelDocking.emplace(docking, std::list<Panel*>()).first;
	}

	p.UpdateDockingState(docking);
	dockIt->second.push_back(&p);

	RecalcLayout();
}

void Layout::Attach(Panel* p, Docking docking)
{
	Attach(*p, docking);
}

void Layout::Detach(Panel* p)
{

}

bool Layout::HasPanel(const Panel* p) const
{
	for (auto dock : _panelDocking) {
		for (auto panel : dock.second) {
			if (panel == p) {
				return true;
			}
		}
	}

	return false;
}

void Layout::AdjustLayout(int cx, int cy, int cw, int ch)
{
	Fl_Widget::resize(cx, cy, cw, ch);

	auto boxoffs = Fl::box_dx(box());
	cx += boxoffs;
	cy += boxoffs;
	cw -= boxoffs;
	ch -= boxoffs;
	auto px = cx;
	auto py = cy;
	auto pw = cw - boxoffs;
	auto ph = ch - boxoffs;

	for (auto dock : _panelDocking)
	{
		auto docking = dock.first;
		for (auto panel : dock.second)
		{
			if (!panel->visible()) {
				continue;
			}

			if (docking == Docking::Left) {
				panel->resize(px, py, panel->w(), ph);
				px += panel->w();
				pw -= panel->w();
			}
			else if (docking == Docking::Top) {
				panel->resize(px, py, pw, panel->h());
				py += panel->h();
				ph -= panel->h();
			}
			else if (docking == Docking::Bottom) {
				panel->resize(px, ch - panel->h(), pw, panel->h());
				ph -= panel->h();
			}
			else if (docking == Docking::Right) {
				panel->resize(cw - panel->w(), py, panel->w(), ph);
				pw -= panel->w();
			}
		}
	}

	if (_centerPanel) {
		_centerPanel->resize(px, py, pw, ph);
	}
}

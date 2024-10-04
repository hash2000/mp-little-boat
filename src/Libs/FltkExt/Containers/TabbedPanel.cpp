#include "TabbedPanel.h"

namespace FltkExt::Containers
{


	TabbedPanel::TabbedPanel(int size, const char* l)
		: Panel(size, l)
	{
		Panel::AttachContent([&](Flex* content) {
			_tabs = std::make_unique<Fl_Tabs>(0, 0, w(), h());
			content->UseBounds(_tabs.get(), false);
			});
	}

	void TabbedPanel::AttachContent(const std::string& title, std::function<void()> proc)
	{
		_tabs->begin();
		auto tab = std::make_unique<Flex>(0, 0, _tabs->w(), _tabs->h() - _tabsSize, Direction::Horz);
		tab->SetLayoutStrategy(LayoutStrategy::Full);
		tab->copy_label(title.c_str());
		tab->begin();
		proc();
		tab->end();
		_tabs->end();
		_tabsGroup.push_back(std::move(tab));
	}

}

#pragma once
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <list>
#include <memory>
#include <functional>
#include <string>

namespace FltkExt::Containers
{


	class TabbedPanel : public Panel
	{
	public:
		TabbedPanel(int size, const char* l);

		void AttachContent(const std::string& title, std::function<void()> proc);

	private:
		int _tabsSize = 20;
		std::unique_ptr<Fl_Tabs> _tabs;
		std::list<std::unique_ptr<Flex>> _tabsGroup;
	};

}

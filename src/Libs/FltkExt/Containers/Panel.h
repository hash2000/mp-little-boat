#pragma once
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Splitter.h"
#include <FL/Fl_Button.H>
#include <string>
#include <memory>
#include <functional>

namespace FltkExt::Containers
{


	class Panel : public Container
	{
		friend class Layout;
	public:
		Panel(int size, const char* l);

		void UpdateDockingState(Docking docking);

		Docking GetDockingState() const;

		void SetMinPanelSize(int size);

		int GetMinPanelSize() const;

		void UseHeader(bool use);

		void UseSplitter(bool use);

		void AttachContent(std::function<void(Flex*)> proc);

		void end() override;

	protected:

		void AdjustLayout(int cx, int cy, int cw, int ch) override;

	private:
		int _minPanelSize = 0;
		Docking _docking = Docking::Center;
		std::unique_ptr<Flex> _topFlex;
		std::unique_ptr<Flex> _topContentFlex;
		std::unique_ptr<Flex> _topHeaderFlex;
		std::unique_ptr<Splitter> _splitter;
		std::unique_ptr<Fl_Button> _hideButton;
		std::unique_ptr<Fl_Button> _pinButton;
	};

}

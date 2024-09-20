#pragma once
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Splitter.h"
#include <FL/Fl_Button.H>
#include <string>
#include <memory>

class Panel : public Container
{
	friend class Layout;

public:
	Panel(int size, const char* l);

	void UpdateDockingState(Docking docking);

	Docking GetDockingState() const;

	void SetMinPanelSize(int size);

	int GetMinPanelSize() const;

protected:

	virtual void AdjustLayout(int cx, int cy, int cw, int ch);

private:
	Docking _docking = Docking::Center;
	std::unique_ptr<Flex> _topFlex;
	std::unique_ptr<Flex> _topContentFlex;
	std::unique_ptr<Flex> _topHeaderFlex;
	std::unique_ptr<Splitter> _splitter;
	std::unique_ptr<Fl_Button> _hideButton;
	std::unique_ptr<Fl_Button> _pinButton;
	int _minPanelSize = 0;

};

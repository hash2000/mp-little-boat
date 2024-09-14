#pragma once
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Splitter.h"
#include <string>
#include <memory>

class Panel : public Container
{
	friend class Layout;

public:
	Panel(int size, const char* l);

	void UpdateDockingState(Docking docking);

	Docking GetDockingState() const;

private:
	Docking _docking = Docking::Center;
	std::unique_ptr<Flex> _topFlex;
	std::unique_ptr<Flex> _topContentFlex;
	std::unique_ptr<Flex> _topHeaderFlex;
	std::unique_ptr<Splitter> _splitter;

};

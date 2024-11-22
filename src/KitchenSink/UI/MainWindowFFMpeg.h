#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Margin.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <string>

class MainWindowFFMpeg : public Fl_Double_Window
{
	using Flex = FltkExt::Containers::Flex;
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using Margin = FltkExt::Containers::Margin;
public:
	MainWindowFFMpeg(const char* label);

};

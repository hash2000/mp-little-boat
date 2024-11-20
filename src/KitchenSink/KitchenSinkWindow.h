#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include "Libs/FltkExt/Containers/Panel.h"
#include "Libs/FltkExt/Containers/Layout.h"
#include <memory>
#include <string>

class KitchenSinkWindow : public Fl_Double_Window
{
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using PushPosition = FltkExt::Containers::PushPosition;
	using Docking = FltkExt::Containers::Docking;
	using Margin = FltkExt::Containers::Margin;
	using Flex = FltkExt::Containers::Flex;
	using Layout = FltkExt::Containers::Layout;
	using Panel = FltkExt::Containers::Panel;
public:
	KitchenSinkWindow();

private:
	void CreateSamplesTree();

	void PopulateSamplesTree();

	void RunSample(const std::string& name);

	void CloseCurrentSample();

private:
	class CurrentSample {
	public:
		std::string _name;
		std::unique_ptr<Fl_Window> _window;

		template <class T> void CreateSample(const std::string& name) {
			_name = name;
			_window = std::make_unique<T>(name.c_str());
			_window->resizable(_window.get());
			_window->show();
		}
	};

	std::unique_ptr<Layout> _layout;
	std::unique_ptr<Panel> _leftPanel;
	std::unique_ptr<Panel> _centerPanel;
	std::unique_ptr<Fl_Tree> _samplesTree;
	std::unique_ptr<CurrentSample> _currentSample;
};

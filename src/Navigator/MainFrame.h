#pragma once
#include <FL/Fl_Double_Window.H>
#include "Libs/FltkExt/Containers/Layout.h"
#include "Navigator/Controls/Toolbars/Toolbar.h"
#include "Navigator/Controls/Files/FilesPanel.h"
#include <memory>

class MainFrame : public Fl_Double_Window
{
public:
	MainFrame();

private:
	std::unique_ptr<FltkExt::Containers::Layout> _layout;
	std::unique_ptr<FilesPanel> _files;
};

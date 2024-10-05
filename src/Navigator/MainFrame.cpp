#include <pch.h>

#include "MainFrame.h"

MainFrame::MainFrame()
	: Fl_Double_Window(1024, 500, "Navigator")
{
	_layout = std::make_unique< FltkExt::Containers::Layout>(0, 0, w(), h());
	{
		_files = std::make_unique<FltkExt::Containers::Panel>(200, "Files tree");
		{

			_files->end();
		}

		_layout->Attach(_files.get(), FltkExt::Containers::Docking::Left);
		_layout->end();
	}
}


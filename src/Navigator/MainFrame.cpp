#include "MainFrame.h"

MainFrame::MainFrame()
	: Fl_Double_Window(1024, 500, "Navigator")
{
	_layout = std::make_unique< FltkExt::Containers::Layout>(0, 0, w(), h());
	_layout->box(FL_FLAT_BOX);
	{
		_files = std::make_unique<FilesPanel>(300, "Files");

		_layout->Attach(_files.get(), FltkExt::Containers::Docking::Left);
		_layout->end();
	}
}


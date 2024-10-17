
#include "MainWindowFlex.h"
#include "MainWindowPanel.h"
#include "MainWindowFltkTable.h"
#include "MainWindowFltkTextEditor.h"
#include "MainWindowFltkThemes.h"
#include "MainWindowFltkSlider.h"
#include "MainWindowFltkTreeOfTables.h"
#include "MainWindowFltkTree.h"
#include "MainWindowGrid.h"
#include "MainWindowList.h"
#include "MainWindowDataTable.h"
#include "MainWindowPickers.h"


int main(int argc, char** argv)
{
	fl_message_hotspot(false);
	fl_message_icon()->labelfont(FL_HELVETICA_BOLD);

	auto wnd = MainWindowPickers{};
	wnd.resizable(wnd);
	wnd.show();
	return Fl::run();
}


#include "UI/MainWindowFlex.h"
#include "UI/MainWindowPanel.h"
#include "UI/MainWindowFltkTable.h"
#include "UI/MainWindowFltkTextEditor.h"
#include "UI/MainWindowFltkThemes.h"
#include "UI/MainWindowFltkSlider.h"
#include "UI/MainWindowFltkTreeOfTables.h"
#include "UI/MainWindowFltkTree.h"
#include "UI/MainWindowGrid.h"
#include "UI/MainWindowList.h"
#include "UI/MainWindowDataTable.h"
#include "UI/MainWindowPickers.h"


int main(int argc, char** argv)
{
	fl_message_hotspot(false);
	fl_message_icon()->labelfont(FL_HELVETICA_BOLD);

	auto wnd = MainWindowPickers{};
	wnd.resizable(wnd);
	wnd.show();
	return Fl::run();
}


#include "Libs/FltkExt/FltkExt.h"
#include "MainWindowFlex.h"
#include "MainWindowPanel.h"
#include "MainWindowFltkTable.h"
#include "MainWindowFltkTextEditor.h"
#include "MainWindowFltkThemes.h"
#include "MainWindowFltkSlider.h"
#include "MainWindowFltkTreeOfTables.h"


int main(int argc, char** argv)
{
	fl_message_hotspot(false);
	fl_message_icon()->labelfont(FL_HELVETICA_BOLD);

	auto wnd = MainWindowFlex{};
	wnd.resizable(wnd);
	wnd.show();
	return Fl::run();
}

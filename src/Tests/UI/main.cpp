
#include "Libs/FltkExt/FltkExt.h"
#include "MainWindowFlex.h"
#include "MainWindowSplitBar.h"
#include "MainWindowFltkTable.h"
#include "MainWindowFltkTextEditor.h"
#include "MainWindowThemes.h"


int main(int argc, char** argv)
{
	fl_message_hotspot(false);
	fl_message_icon()->labelfont(FL_HELVETICA_BOLD);

	auto wnd = MainWindowThemes{};
	wnd.resizable(wnd);
	wnd.show();
	return Fl::run();
}

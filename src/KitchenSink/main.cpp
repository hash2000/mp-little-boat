#include "FltkAll.h"
#include "KitchenSinkWindow.h"


int main(int argc, char** argv)
{
	fl_message_hotspot(false);
	fl_message_icon()->labelfont(FL_HELVETICA_BOLD);

	auto wnd = KitchenSinkWindow{};
	wnd.resizable(wnd);
	wnd.show();
	return Fl::run();
}

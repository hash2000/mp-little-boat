#include <pch.h>
#include <Poco/Util/Application.h>

#include "Common/core/Kernel.h"
#include "MainFrame.h"

class NavigatorApplication : public Poco::Util::Application
{
public:
	int main(const ArgVec& args) override
	{
		logger().information("Application Navigator Start");
		logger().information("Current directory: " + Poco::Path::current());

		try {
			InternalMain(args);
		}
		catch (Poco::Exception& exception) {
			logger().error(exception.displayText());
		}

		logger().information("Application Navigator End");
		return Poco::Util::Application::EXIT_OK;
	}

private:

	void BuildServices(const Ioc::Kernel& kernel)
	{
	}

	void InternalMain(const ArgVec& args)
	{
		fl_message_hotspot(false);
		fl_message_icon()->labelfont(FL_HELVETICA_BOLD);
		MainFrame mainWnd;
		mainWnd.resizable(mainWnd);
		mainWnd.show();
//		struct Fl_Enable_Dark_Mode {
//			Fl_Enable_Dark_Mode() {
//#if _WIN32
//				Fl::background(25, 25, 25);
//				Fl::background2(32, 32, 32);
//				Fl::foreground(255, 255, 255);
//				Fl::set_color(FL_SELECTION_COLOR, 0, 160, 250);
//#elif __APPLE__
//				Fl::background(50, 50, 50);
//				Fl::background2(23, 23, 23);
//				Fl::foreground(223, 223, 223);
//				Fl::set_color(FL_SELECTION_COLOR, 0, 87, 207);
//#else
//				Fl::background(51, 51, 51);
//				Fl::background2(45, 45, 45);
//				Fl::foreground(255, 255, 255);
//				Fl::set_color(FL_SELECTION_COLOR, 21, 83, 158);
//#endif
//			}
//		} enable_dark_mode; // Must be call after window.show, because show(...) method init system colors and reset selection color to 0xf.
		Fl::run();
	}
};

POCO_APP_MAIN(NavigatorApplication)

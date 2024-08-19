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
		//fl_message_hotspot(false);
		//fl_message_icon()->labelfont(FL_HELVETICA_BOLD);
		//Fl::background(25, 25, 25);
		//Fl::background2(32, 32, 32);
		//Fl::foreground(255, 255, 255);
		//Fl::set_color(FL_SELECTION_COLOR, 0, 160, 250);

		MainFrame mainWnd;
		mainWnd.resizable(mainWnd);
		mainWnd.show();
		Fl::run();
	}
};

POCO_APP_MAIN(NavigatorApplication)

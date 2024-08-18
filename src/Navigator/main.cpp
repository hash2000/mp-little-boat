#include <pch.h>
#include <Poco/Util/Application.h>
#include <FL/Fl_Window.H>

#include "Common/core/Kernel.h"

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
		Fl_Window mainWnd(720, 648);
		mainWnd.resizable(mainWnd);
		mainWnd.show();
		Fl::run();
	}
};

POCO_APP_MAIN(NavigatorApplication)

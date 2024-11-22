#include "FltkAll.h"
#include "KitchenSinkWindow.h"
#include "Common/core/Kernel.h"
#include <Poco/Util/Application.h>
#include <memory>

class KitchenSinkApplication : public Poco::Util::Application
{
public:
	int main(const ArgVec& args) override
	{
		logger().information("Application KitchenSink Start");
		logger().information("Current directory: " + Poco::Path::current());

		try {
			InternalMain(args);
		}
		catch (Poco::Exception& exception) {
			logger().error(exception.displayText());
		}

		logger().information("Application KitchenSink End");
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
		auto mainWnd = std::make_unique<KitchenSinkWindow>();
		mainWnd->resizable(mainWnd.get());
		mainWnd->show();
		mainWnd->RunSample("fltkext/Video/FFMpeg");
		Fl::run();
	}
};

POCO_APP_MAIN(KitchenSinkApplication)

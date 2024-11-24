#include "FltkAll.h"
#include "KitchenSinkWindow.h"
#include "Common/core/Kernel.h"
#include "Modules/ModuleContainer/IModuleContainer.h"
#include "Modules/ModuleContainer/IModuleContainerFactory.h"
#include "Modules/StreamingContainer/IStreamingContainerFactory.h"

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

	void InternalMain(const ArgVec& args)
	{
		auto module = ModuleContainerFactory::Make();
		auto kernel = module->GetKernel();
		module->Initialize();
		kernel.AddInstance<IModuleContainer>(module);

		BuildServices(kernel);
		RunMainFrame(kernel);
	}

	void BuildServices(Ioc::Kernel& kernel)
	{
		StreamingContainerFactory::Make()->Build(kernel);
	}

	void RunMainFrame(Ioc::Kernel& kernel)
	{
		fl_message_hotspot(false);
		fl_message_icon()->labelfont(FL_HELVETICA_BOLD);
		auto mainWnd = std::make_unique<KitchenSinkWindow>(kernel);
		mainWnd->resizable(mainWnd.get());
		mainWnd->show();
		mainWnd->RunSample("fltkext/Video/FFMpeg", kernel);
		Fl::run();
	}
};

POCO_APP_MAIN(KitchenSinkApplication)

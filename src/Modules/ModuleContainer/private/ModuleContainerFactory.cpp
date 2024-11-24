#include "Modules/ModuleContainer/IModuleContainerFactory.h"
#include "Modules/ModuleContainer/private/ModuleContainer.h"


namespace ModuleContainerFactory
{
	std::shared_ptr<IModuleContainer> Make()
	{
		return std::make_shared<ModuleContainer>();
	}
}

#pragma once
#include "Modules/ModuleContainer/IModuleContainer.h"
#include "Modules/ModuleContainer/IModuleContainerBuilder.h"

namespace ModuleContainerFactory
{
	std::shared_ptr<IModuleContainer> Make();
}


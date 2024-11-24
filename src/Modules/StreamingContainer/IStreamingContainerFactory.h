#pragma once
#include "Modules/ModuleContainer/IModuleContainerBuilder.h"

namespace StreamingContainerFactory
{
	std::shared_ptr<IModuleContainerBuilder> Make();
}

#include "ModuleContainer.h"

std::shared_ptr<IModuleContainer> IModuleContainer::Make()
{
	return std::make_shared<ModuleContainer>();
}


ModuleContainer::ModuleContainer()
{
}

void ModuleContainer::Initialize()
{

}

void ModuleContainer::Shutdown()
{

}

Ioc::Kernel& ModuleContainer::GetKernel()
{
	return _kernel;
}

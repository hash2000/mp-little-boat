#include "ModuleContainer.h"

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

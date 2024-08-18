#include <pch.h>
#include "Libs/ModuleManager/private/ModuleManager.h"

std::shared_ptr<IModuleManager> IModuleManager::Make()
{
	return std::make_shared<ModuleManager>();
}


ModuleManager::ModuleManager()
{
}

void ModuleManager::Initialize()
{

}

void ModuleManager::Shutdown()
{

}

Ioc::Kernel& ModuleManager::GetKernel()
{
	return _kernel;
}

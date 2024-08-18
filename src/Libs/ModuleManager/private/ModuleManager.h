#pragma once
#include "Libs/ModuleManager/IModuleManager.h"

class ModuleManager : public IModuleManager
{
public:
	ModuleManager();

	void Initialize() override;

	void Shutdown() override;

	Ioc::Kernel& GetKernel() override;

private:
	Ioc::Kernel _kernel;
};

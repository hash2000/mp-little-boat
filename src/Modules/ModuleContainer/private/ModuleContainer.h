#pragma once
#include "Modules/ModuleContainer/IModuleContainer.h"

class ModuleContainer : public IModuleContainer
{
public:
	ModuleContainer();

	void Initialize() override;

	void Shutdown() override;

	Ioc::Kernel& GetKernel() override;

private:
	Ioc::Kernel _kernel;
};

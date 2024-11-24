#pragma once
#include <memory>
#include "Common/core/Kernel.h"

class IModuleContainer
{
public:
	virtual ~IModuleContainer() = default;

	virtual void Initialize() = 0;

	virtual void Shutdown() = 0;

	virtual Ioc::Kernel& GetKernel() = 0;

};

#pragma once
#include <memory>
#include "Common/core/Kernel.h"

class IModuleManager
{
public:
	static std::shared_ptr<IModuleManager> Make();

public:
	virtual ~IModuleManager() = default;

	virtual void Initialize() = 0;

	virtual void Shutdown() = 0;

	virtual Ioc::Kernel& GetKernel() = 0;

};

#pragma once
#include "Common/core/Kernel.h"

class IModuleContainerBuilder
{
public:
	virtual ~IModuleContainerBuilder() = default;

	virtual void Build(Ioc::Kernel& kernel) = 0;
};

#pragma once
#include "Common/core/Kernel.h"
#include "Modules/ModuleContainer/IModuleContainerBuilder.h"

class StreamingContainerBuilder : public IModuleContainerBuilder
{
public:
	virtual ~StreamingContainerBuilder() = default;

	void Build(Ioc::Kernel& kernel) override;
};


#pragma once
#include "Modules/ModuleContainer/IModuleContainerBuilder.h"

class StreamingContainerBuilder
{
public:
	virtual ~StreamingContainerBuilder() = default;

	static std::shared_ptr<IModuleContainerBuilder> Make();

	void Build(Ioc::Kernel& kernel) override;
};

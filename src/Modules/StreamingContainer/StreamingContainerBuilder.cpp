#include "StreamingContainerBuilder.h"

std::shared_ptr<IModuleContainerBuilder> StreamingContainerBuilder::Make()
{
	return std::shared_ptr<StreamingContainerBuilder>();
}

void StreamingContainerBuilder::Build(Ioc::Kernel& kernel)
{
}

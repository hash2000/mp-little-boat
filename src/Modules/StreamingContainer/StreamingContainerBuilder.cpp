#include "StreamingContainerBuilder.h"

std::shared_ptr<IModuleContainerBuilder> StreamingContainerBuilder::Make()
{
	return std::make_shared<StreamingContainerBuilder>();
}

void StreamingContainerBuilder::Build(Ioc::Kernel& kernel)
{
}

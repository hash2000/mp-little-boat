#include "StreamingContainerBuilder.h"
#include "private/StreamingContainer.h"

void StreamingContainerBuilder::Build(Ioc::Kernel& kernel)
{
	kernel.AddTransientAbstraction<IStreamingContainer, StreamingContainer>();
}

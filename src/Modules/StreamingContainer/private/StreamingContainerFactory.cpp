#include "Modules/StreamingContainer/IStreamingContainerFactory.h"
#include "StreamingContainerBuilder.h"


namespace StreamingContainerFactory
{
	std::shared_ptr<IModuleContainerBuilder> Make()
	{
		return std::make_shared<StreamingContainerBuilder>();
	}
}

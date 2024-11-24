#include "Modules/StreamingContainer/IStreamingContainer.h"
#include "Modules/StreamingContainer/private/Pipeline/Pipeline.h"

class StreamingContainer : public IStreamingContainer
{
public:
	StreamingContainer(const Ioc::Kernel& kernel);
};

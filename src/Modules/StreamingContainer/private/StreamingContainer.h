#include "Modules/StreamingContainer/IStreamingContainer.h"
#include "Modules/StreamingContainer/private/Pipeline/Pipeline.h"
#include "Modules/StreamingContainer/private/FFMpeg/PipeContext.h"
#include <string>

class StreamingContainer : public IStreamingContainer
{
public:
	StreamingContainer(const Ioc::Kernel& kernel);

	void SetFile(const std::string& path);

	void Initialize() override;

	void Shutdown() override;

private:
	Pipeline _pipeline;
};

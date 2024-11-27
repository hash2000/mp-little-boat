#include "Modules/StreamingContainer/IStreamingContainer.h"
#include "Modules/StreamingContainer/private/Pipeline/Pipeline.h"
#include "Modules/StreamingContainer/private/FFMpeg/PipeContext.h"
#include <string>

class StreamingContainer : public IStreamingContainer
{
public:
	StreamingContainer(const Ioc::Kernel& kernel);

	void Initialize() override;

	void Shutdown() override;

	void SetFile(const std::string& path) override;

	const std::list<std::string>& GetMessages() const override;

private:
	Pipeline _pipeline;
};

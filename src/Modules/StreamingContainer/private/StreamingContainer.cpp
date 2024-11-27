#include "StreamingContainer.h"
#include "Modules/StreamingContainer/private/FFMpeg/RegisterCodecsPipe.h"
#include "Modules/StreamingContainer/private/FFMpeg/RegisterAvFormatPipe.h"
#include "Modules/StreamingContainer/private/FFMpeg/RegisterDecoderPipe.h"

StreamingContainer::StreamingContainer(const Ioc::Kernel& kernel)
{
	_pipeline.Add<RegisterCodecsPipe>();
	_pipeline.Add<RegisterAvFormatPipe>();
	_pipeline.Add<RegisterDecoderPipe>();
}

void StreamingContainer::SetFile(const std::string& path)
{
	_pipeline.GetContext().SetFile(path);
}

void StreamingContainer::Initialize()
{
	_pipeline.Build();
}

void StreamingContainer::Shutdown()
{
	_pipeline.Rollback();
}

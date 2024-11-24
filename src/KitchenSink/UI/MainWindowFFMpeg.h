#pragma once
#include "Common/core/Kernel.h"
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Margin.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include "Modules/StreamingContainer/IStreamingContainer.h"
#include <string>
#include <memory>
#include <Poco/FileStream.h>

class MainWindowFFMpeg : public Fl_Double_Window
{
	using Flex = FltkExt::Containers::Flex;
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using Margin = FltkExt::Containers::Margin;
public:
	MainWindowFFMpeg(const char* label, const Ioc::Kernel& kernel);

protected:
	void OnBuffer(Fl_Button* widget);

private:
	std::shared_ptr<IStreamingContainer> _streaming;
	std::unique_ptr<Poco::FileStream> _stream;
	std::string _videoFile = "c:\\video_test.mp4";
};

#pragma once
#include "FltkAll.h"
#include "Libs/FltkExt/Containers/Flex.h"
#include "Libs/FltkExt/Containers/Margin.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <string>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
}

class MainWindowFFMpeg : public Fl_Double_Window
{
	using Flex = FltkExt::Containers::Flex;
	using Direction = FltkExt::Containers::Direction;
	using LayoutStrategy = FltkExt::Containers::LayoutStrategy;
	using Margin = FltkExt::Containers::Margin;
public:
	MainWindowFFMpeg(const char* label);

};

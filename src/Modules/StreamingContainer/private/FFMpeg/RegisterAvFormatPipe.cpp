#include "RegisterAvFormatPipe.h"
#include "FFMpegError.h"
#include "sstream"

bool RegisterAvFormatPipe::InternalBuild(PipeContext& context)
{
	FFMpegError error;

	auto filePath = context.GetFile();
	auto inputFormat = context.GetInputFormatName();
	if (!inputFormat.empty()) {
		auto format =  av_find_input_format(inputFormat.c_str());
		if (format) {
			context.SetInputFormat(format);
		}
		else {
			context.SetMessage("INFO: MP: Unable to find input format for: " + filePath);
		}
	}

	AVDictionary* opts = nullptr;
	auto bufferSize = context.GetBuffering();
	if (bufferSize && context.GetFile().empty()) {
		av_dict_set_int(&opts, "buffer_size", bufferSize, 0);
	}

	auto ffmpegOpts = context.GetFFMpegOpts();
	if (!ffmpegOpts.empty()) {
		error.Parse(av_dict_parse_string(&opts, ffmpegOpts.c_str(), "=", " ", 0));
		if (error.HasError()) {
			std::stringstream message;
			message << "WARNING: Failed to parse FFmpeg options: "
				<< error.GetText() << std::endl << ffmpegOpts;
			context.SetMessage(message.str());
		}
	}

	auto formatContext = avformat_alloc_context();
	if (bufferSize == 0) {
		formatContext->flags |= AVFMT_FLAG_NOBUFFER;
	}

	if (!context.IsLocalFile()) {
		av_dict_set(&opts, "stimeout", "30000000", 0);
		formatContext->interrupt_callback.opaque = nullptr;
		formatContext->interrupt_callback.callback = [](void*){
			//mp_media_t* m = data;
			
			return 0; // rreturn 1 if stop
			};
	}

	error.Parse(avformat_open_input(&formatContext, filePath.c_str(), context.GetInputFormat(), opts ? &opts : nullptr));
	av_dict_free(&opts);

	if (error.HasError()) {
		if (!context.IsReconnectiong()) {
			context.SetMessage("WARNING: MP: Failed to find stream info for: " + filePath);
		}
		context.SetMessage(error.GetText());
		return false;
	}

	context.UseReconnecting(false);
	context.SetFormatContext(formatContext);

	return true;
}

void RegisterAvFormatPipe::InternalRollback(PipeContext& context)
{
	auto formatContext = context.GetFormatContext();
	context.SetFormatContext(nullptr);
	if (formatContext) {
		avformat_close_input(&formatContext);
	}

}

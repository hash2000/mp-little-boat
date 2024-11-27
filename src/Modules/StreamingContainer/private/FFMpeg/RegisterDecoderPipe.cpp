#include "RegisterDecoderPipe.h"
#include "FFMpegError.h"

namespace {
	enum AVHWDeviceType _hardware_priority[] = {
		AV_HWDEVICE_TYPE_CUDA,  AV_HWDEVICE_TYPE_D3D11VA, AV_HWDEVICE_TYPE_DXVA2,        AV_HWDEVICE_TYPE_VAAPI,
		AV_HWDEVICE_TYPE_VDPAU, AV_HWDEVICE_TYPE_QSV,     AV_HWDEVICE_TYPE_VIDEOTOOLBOX, AV_HWDEVICE_TYPE_NONE,
	};
}

bool RegisterDecoderPipe::InternalBuild(PipeContext& context)
{
	if (!Init(context, AVMEDIA_TYPE_VIDEO)) {
		return false;
	}

	if (!Init(context, AVMEDIA_TYPE_AUDIO)) {
		return false;
	}

	return true;
}

void RegisterDecoderPipe::InternalRollback(PipeContext& context)
{
	Shutdown(context, AVMEDIA_TYPE_VIDEO);
	Shutdown(context, AVMEDIA_TYPE_AUDIO);
}

bool RegisterDecoderPipe::Init(PipeContext& context, AVMediaType type)
{
	FFMpegError error;
	auto format = context.GetFormatContext();
	auto hardware = context.IsHardwareDecode(type);

	error.Parse(av_find_best_stream(format, type, -1, -1, nullptr, 0));
	if (error.GetCode() < 0) {
		return false;
	}

	auto stream = format->streams[error.GetCode()];
	auto id = stream->codecpar->codec_id;
	const AVCodec* codec = nullptr;

	context.SetStream(stream, type);

	if (type == AVMEDIA_TYPE_VIDEO) {
		context.SetMaxLuminance(GetMaxLuminance(stream), type);
	}

	if (id == AV_CODEC_ID_VP8 || id == AV_CODEC_ID_VP9)
	{
		AVDictionaryEntry* tag = NULL;
		tag = av_dict_get(stream->metadata, "alpha_mode", tag, AV_DICT_IGNORE_SUFFIX);

		if (tag && strcmp(tag->value, "1") == 0) {
			auto codecName = (id == AV_CODEC_ID_VP8) ? "libvpx" : "libvpx-vp9";
			codec = avcodec_find_decoder_by_name(codecName);
			context.SetCodec(codec, type);
		}
	}

	if (!codec) {
		codec = avcodec_find_decoder(id);
	}

	if (!codec) {
		context.SetMesssage("WARNING: MP: Failed to find " + std::string(av_get_media_type_string(type)) + " codec");
		return false;
	}

	if (!OpenCodec(context, type)) {
		return false;
	}

	return true;
}

void RegisterDecoderPipe::Shutdown(PipeContext& context, AVMediaType type)
{
	auto codecContext = context.GetCodecContext(type);
	context.SetCodecContext(nullptr, type);

	avcodec_free_context(&codecContext);
}

bool RegisterDecoderPipe::OpenCodec(PipeContext& context, AVMediaType type)
{
	FFMpegError error;
	auto codec = context.GetCodec(type);
	auto stream = context.GetStream(type);
	auto hardware = context.IsHardwareDecode(type);

	auto codecContext = avcodec_alloc_context3(codec);
	if (!codecContext) {
		context.SetMesssage("WARNING: MP: Failed to allocate context");
		return false;
	}

	context.SetCodecContext(codecContext, type);

	error.Parse(avcodec_parameters_to_context(codecContext, stream->codecpar));
	if (error.GetCode() < 0) {
		return false;
	}

	context.UseHardwareDecode(false, type);

	if (hardware) {
		OpenHardwareDecoder(context, type);
	}

	error.Parse(avcodec_open2(codecContext, codec, nullptr));
	if (error.GetCode() < 0) {
		return false;
	}

	return true;
}

void RegisterDecoderPipe::OpenHardwareDecoder(PipeContext& context, AVMediaType type)
{
	FFMpegError error;
	auto codeс = context.GetCodec(type);
	auto codecContext = context.GetCodecContext(type);
	auto priority = _hardware_priority;
	AVBufferRef* hardwareContext = nullptr;
	AVPixelFormat pixFormat;

	while (*priority != AV_HWDEVICE_TYPE_NONE)
	{
		if (HasHardwareType(codeс, *priority, &pixFormat)) {
			error.Parse(av_hwdevice_ctx_create(&hardwareContext, *priority, nullptr, nullptr, 0));
			if (!error.HasError()) {
				break;
			}
		}

		priority++;
	}

	if (hardwareContext)
	{
		codecContext->hw_device_ctx = av_buffer_ref(hardwareContext);
		codecContext->opaque = &context;
		context.UseHardwareDecode(true);
		context.SetHardwareContext(hardwareContext);
	}
}

bool RegisterDecoderPipe::HasHardwareType(const AVCodec* codec, AVHWDeviceType type, AVPixelFormat* hw_format)
{
	for (int i = 0;; i++)
	{
		auto config = avcodec_get_hw_config(codec, i);
		if (!config) {
			break;
		}

		if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && config->device_type == type)
		{
			*hw_format = config->pix_fmt;
			return true;
		}
	}

	return false;
}

uint16_t RegisterDecoderPipe::GetMaxLuminance(const AVStream* stream)
{
	uint32_t max_luminance = 0;

	for (int i = 0; i < stream->codecpar->nb_coded_side_data; i++) {
		const AVPacketSideData* const sd = &stream->codecpar->coded_side_data[i];
		switch (sd->type) {
		case AV_PKT_DATA_MASTERING_DISPLAY_METADATA: {
			const AVMasteringDisplayMetadata* mastering = (AVMasteringDisplayMetadata*)sd->data;
			if (mastering->has_luminance) {
				max_luminance = (uint32_t)(av_q2d(mastering->max_luminance) + 0.5);
			}

			break;
		}
		case AV_PKT_DATA_CONTENT_LIGHT_LEVEL: {
			const AVContentLightMetadata* const md = (AVContentLightMetadata*)&sd->data;
			max_luminance = md->MaxCLL;
			break;
		}
		default:
			break;
		}
	}

	return max_luminance;
}

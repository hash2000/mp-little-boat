#include "PipeContext.h"
#include <sstream>

void PipeContext::SetMessage(const std::string& message) {
	_messages.push_back(message);
}

void PipeContext::SetFile(const std::string& file)
{
	_input._file = file;
	_input._isLocalFile = true;
	SetMessage("INFO: Use local file: " + file);
}

void PipeContext::SetInputFormatName(const std::string& name)
{
	_input._format = name;
	SetMessage("INFO: Use input format: " + name);
}

void PipeContext::SetInputFormat(const AVInputFormat* set)
{
	_input._inputFormat = set;
	SetInputFormatMessage(set);
}

void PipeContext::SetFormatContext(AVFormatContext* set)
{
	_input._formatContext = set;

	if (set) {
		SetInputFormatMessage(set->iformat);
	}
}

void PipeContext::SetCodec(const AVCodec* codec, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._codec = codec;
	}
	else {
		_audio._codec = codec;
	}

	SetCodecMessage(codec, type);
}

void PipeContext::SetStream(AVStream* stream, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._stream = stream;
	}
	else {
		_audio._stream = stream;
	}
}

void PipeContext::SetCodecContext(AVCodecContext* context, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._context = context;
	}
	else {
		_audio._context = context;
	}
}

void PipeContext::SetHardwareContext(AVBufferRef* context, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._hardwareContext = context;
	}
	else {
		_audio._hardwareContext = context;
	}

	std::stringstream text;
	text << "INFO: Use hardware decoder of MediaType [" << GetMediaTypeName(type) << "] size: "
		<< context->size << " bytes";

	SetMessage(text.str());
}

void PipeContext::SetBuffering(int set) {
	_input._buffering = set;
}

void PipeContext::SetFFMpegOpts(const std::string& opts)
{
	_input._ffmpegOpts = opts;
	SetMessage("INFO: Use FFMpeg options: " + opts);
}

void PipeContext::SetMaxLuminance(uint16_t set, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._maxLuminance = set;
	}
	else {
		_audio._maxLuminance = set;
	}

	std::stringstream text;
	text << "INFO: Use max luminance of MediaType [" << GetMediaTypeName(type) << "] " << set;
	SetMessage(text.str());
}

void PipeContext::UseReconnecting(bool set) {
	_input._reconnecting = set;
}

void PipeContext::UseHardwareDecode(bool set, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._hardware = set;
	}
	else {
		_audio._hardware = set;
	}
}

const std::list<std::string>& PipeContext::GetMessages() const {
	return _messages;
}

bool PipeContext::IsCached() const {
	return _input._isFullDecode && _input._isLocalFile;
}

bool PipeContext::IsLocalFile() const {
	return _input._isLocalFile;
}

bool PipeContext::IsReconnectiong() const {
	return _input._reconnecting;
}

bool PipeContext::IsHardwareDecode(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._hardware : _audio._hardware;
}

int PipeContext::GetBuffering() const {
	return _input._buffering;
}

uint16_t PipeContext::GetMaxLuminance(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._maxLuminance : _audio._maxLuminance;
}

const AVInputFormat* PipeContext::GetInputFormat() const {
	return _input._inputFormat;
}

AVFormatContext* PipeContext::GetFormatContext() const {
	return _input._formatContext;
}

std::string PipeContext::GetFile() const {
	return _input._file;
}

std::string PipeContext::GetInputFormatName() const {
	return _input._format;
}

std::string PipeContext::GetFFMpegOpts() const {
	return _input._ffmpegOpts;
}

const AVCodec* PipeContext::GetCodec(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._codec : _audio._codec;
}

AVStream* PipeContext::GetStream(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._stream : _audio._stream;
}

AVCodecContext* PipeContext::GetCodecContext(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._context : _audio._context;
}

AVBufferRef* PipeContext::GetHardwareContext(AVMediaType type) const {
	return type == AVMEDIA_TYPE_VIDEO ? _video._hardwareContext : _audio._hardwareContext;
}

void PipeContext::SetInputFormatMessage(const AVInputFormat* fmt)
{
	if (!fmt) {
		return;
	}

	std::stringstream text;
	text << "INFO: Use input format: " << fmt->name << " info: " << fmt->long_name;
	SetMessage(text.str());
}

void PipeContext::SetCodecMessage(const AVCodec* codec, AVMediaType type)
{
	if (!codec) {
		return;
	}

	std::stringstream text;
	text << "INFO: Use codec: " << codec->name << " info: " << codec->long_name
		<< " of MediaType: " << GetMediaTypeName(type);
	SetMessage(text.str());
}

std::string PipeContext::GetMediaTypeName(AVMediaType type) {
	return type == AVMEDIA_TYPE_VIDEO ? "video" : "audio";
}

std::string PipeContext::GetBooleanValueName(bool value) {
	return value ? "true" : "false";
}

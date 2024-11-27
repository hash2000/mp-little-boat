#include "PipeContext.h"

void PipeContext::SetMesssage(const std::string& message) {
	_messages.push_back(message);
}

void PipeContext::SetFile(const std::string& file) {
	_input._file = file;
	_input._isLocalFile = true;
}

void PipeContext::SetInputFormatName(const std::string& name) {
	_input._format = name;
}

void PipeContext::SetInputFormat(const AVInputFormat* set) {
	_input._inputFormat = set;
}

void PipeContext::SetFormatContext(AVFormatContext* set) {
	_input._formatContext = set;
}

void PipeContext::SetCodec(const AVCodec* codec, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._codec = codec;
	}
	else {
		_audio._codec = codec;
	}
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
}

void PipeContext::SetBuffering(int set) {
	_input._buffering = set;
}

void PipeContext::SetFFMpegOpts(const std::string& opts) {
	_input._ffmpegOpts = opts;
}

void PipeContext::SetMaxLuminance(uint16_t set, AVMediaType type)
{
	if (type == AVMEDIA_TYPE_VIDEO) {
		_video._maxLuminance = set;
	}
	else {
		_audio._maxLuminance = set;
	}
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

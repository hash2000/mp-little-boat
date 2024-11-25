#include "PipeContext.h"

void PipeContext::SetMesssage(const std::string& message) {
	_messages.push_back(message);
}

void PipeContext::SetFile(const std::string& file) {
	_params._file = file;
	_isLocalFile = true;
}

void PipeContext::SetInputFormatName(const std::string& name) {
	_params._format = name;
}

void PipeContext::SetInputFormat(const AVInputFormat* set) {
	_inputFormat = set;
}

void PipeContext::SetFormatContext(AVFormatContext* set) {
	_formatContext = set;
}

void PipeContext::SetBuffering(int set) {
	_params._buffering = set;
}

void PipeContext::SetFFMpegOpts(const std::string& opts) {
	_params._ffmpegOpts = opts;
}

void PipeContext::SetReconnecting(bool set)
{
	_params._reconnecting = set;
}

const std::list<std::string>& PipeContext::GetMessages() const {
	return _messages;
}

bool PipeContext::IsCached() const {
	return _isFullDecode && _isLocalFile;
}

bool PipeContext::IsLocalFile() const {
	return _isLocalFile;
}

bool PipeContext::IsReconnectiong() const {
	return _params._reconnecting;
}

int PipeContext::GetBuffering() const {
	return _params._buffering;
}

const AVInputFormat* PipeContext::GetInputFormat() const {
	return _inputFormat;
}


AVFormatContext* PipeContext::GetFormatContext() const {
	return _formatContext;
}

std::string PipeContext::GetFile() const {
	return _params._file;
}

std::string PipeContext::GetInputFormatName() const {
	return _params._format;
}

std::string PipeContext::GetFFMpegOpts() const {
	return _params._ffmpegOpts;
}


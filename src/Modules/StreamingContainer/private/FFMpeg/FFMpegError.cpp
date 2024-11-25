#include "FFMpegError.h"

FFMpegError::FFMpegError()
	: _code(0)
{
}

FFMpegError::FFMpegError(int code)
{
	Parse(code);
}

void FFMpegError::Parse(int code)
{
	Clear();
	_error.resize(MaxErrorStringSize);
	av_strerror(code, &_error[0], MaxErrorStringSize);
	size_t len = std::strlen(_error.c_str());
	_error.resize(len);
	_code = code;
}

std::string FFMpegError::GetText() const
{
	return _error;
}

bool FFMpegError::HasError() const
{
	return _code != 0;
}

int FFMpegError::GetCode() const
{
	return _code;
}

void FFMpegError::Clear()
{
	_code = 0;
	_error.clear();
}

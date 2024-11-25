#pragma once
#include "hardware.h"
#include <string>

class FFMpegError
{
public:
	static constexpr int MaxErrorStringSize = 64;

public:
	FFMpegError();

	FFMpegError(int code);

	void Parse(int code);

	std::string GetText() const;

	bool HasError() const;

	int GetCode() const;

	void Clear();

private:
	int _code;
	std::string _error;
};

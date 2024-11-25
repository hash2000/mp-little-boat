#pragma once
#include "Common/core/Kernel.h"
#include <string>

class IStreamingContainer
{
public:
	virtual ~IStreamingContainer() = default;

	virtual void SetFile(const std::string& path) = 0;

	virtual void Initialize() = 0;

	virtual void Shutdown() = 0;
};

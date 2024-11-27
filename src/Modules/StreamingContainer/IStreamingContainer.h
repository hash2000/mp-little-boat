#pragma once
#include "Common/core/Kernel.h"
#include <string>
#include <list>

class IStreamingContainer
{
public:
	virtual ~IStreamingContainer() = default;

	virtual void SetFile(const std::string& path) = 0;

	virtual void Initialize() = 0;

	virtual void Shutdown() = 0;

	virtual const std::list<std::string>& GetMessages() const = 0;
};

#pragma once
#include <string>

class ILoggerManager
{
public:

	virtual void Append(const std::string& message) = 0;
};

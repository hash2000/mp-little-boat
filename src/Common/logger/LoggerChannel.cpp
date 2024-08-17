#include "pch.h"
#include "LoggerChannel.h"
#include <sstream>

LoggerChannel::LoggerChannel(ILoggerManager* loggerManager)
	: _loggerManager(loggerManager)
{
	_formatter.setProperty("pattern", "[%Y-%m-%dT%H:%M:%S] %p: %t");
}

void LoggerChannel::log(const Poco::Message& msg)
{
	std::string result;
	_formatter.format(msg, result);
	_loggerManager->Append(result);
}

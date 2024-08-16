#pragma once
#include "ILoggerManager.h"
#include <Poco/Channel.h>
#include <Poco/Message.h>
#include <Poco/PatternFormatter.h>

class LoggerChannel : public Poco::Channel
{
public:
	LoggerChannel(ILoggerManager* loggerManager);

	void log(const Poco::Message& msg);

private:
	ILoggerManager* _loggerManager;
	Poco::PatternFormatter _formatter;
};


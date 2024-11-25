#pragma once
#include "hardware.h"
#include "Pipeline/Pipe.h"

class RegisterAvFormatPipe : public Pipe
{
public:
	bool InternalBuild(PipeContext& context) override;

	void InternalRollback(PipeContext& context) override;
};

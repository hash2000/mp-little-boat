#pragma once
#include "PipeContext.h"

class Pipe
{
public:
	virtual void Build(PipeContext& context)
	{
	}

	virtual void Rollback(PipeContext& context)
	{
	}
};


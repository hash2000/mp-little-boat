#pragma once
#include "hardware.h"
#include "Pipeline/Pipe.h"

class RegisterCodecsPipe : public Pipe
{
public:
	bool InternalBuild(PipeContext& context) override;

	void InternalRollback(PipeContext& context) override;

private:

	void BuildCache();

	void BuildMedia();
};
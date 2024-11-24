#pragma once
#include "hardware.h"
#include "Pipeline/Pipe.h"

class RegisterCodecsPipe : public Pipe
{
public:
	void Build(PipeContext& context) override;

	void Rollback(PipeContext& context) override;

private:

	void BuildCache();

	void BuildMedia();
};

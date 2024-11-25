#pragma once
#include "Modules/StreamingContainer/private/FFMpeg/PipeContext.h"

class Pipe
{
public:
	void Build(PipeContext& context)
	{
		if (!_initialized) {
			if (InternalBuild(context)) {
				_initialized = true;
			}
		}
	}

	void Rollback(PipeContext& context)
	{
		if (_initialized) {
			InternalRollback(context);
			_initialized = false;
		}
	}

protected:
	virtual bool InternalBuild(PipeContext& context) {
		return true;
	}

	virtual void InternalRollback(PipeContext& context) {
	}

private:
	bool _initialized = false;

};


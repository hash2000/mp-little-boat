#include "RegisterCodecsPipe.h"

bool RegisterCodecsPipe::InternalBuild(PipeContext& context)
{
	if (context.IsCached()) {
		BuildCache();
		BuildMedia();
	}
	else {
		BuildMedia();
	}

	return true;
}

void RegisterCodecsPipe::InternalRollback(PipeContext& context)
{

}

void RegisterCodecsPipe::BuildCache()
{
	avdevice_register_all();
	avformat_network_init();
}

void RegisterCodecsPipe::BuildMedia()
{

}

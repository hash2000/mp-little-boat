#include "RegisterCodecsPipe.h"

void RegisterCodecsPipe::Build(PipeContext& context)
{
	BuildCache();
	BuildMedia();
}

void RegisterCodecsPipe::Rollback(PipeContext& context)
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

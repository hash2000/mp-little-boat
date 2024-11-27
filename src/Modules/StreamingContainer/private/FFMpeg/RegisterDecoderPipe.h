#pragma once
#include "hardware.h"
#include "Pipeline/Pipe.h"

class RegisterDecoderPipe : public Pipe
{
public:
	bool InternalBuild(PipeContext& context) override;

	void InternalRollback(PipeContext& context) override;

private:

	bool Init(PipeContext& context, AVMediaType type);

	void Shutdown(PipeContext& context, AVMediaType type);

	bool OpenCodec(PipeContext& context, AVMediaType type);

	void OpenHardwareDecoder(PipeContext& context, AVMediaType type);

	bool HasHardwareType(const AVCodec* codec, AVHWDeviceType type, AVPixelFormat* hw_format);

	uint16_t GetMaxLuminance(const AVStream* stream);

};

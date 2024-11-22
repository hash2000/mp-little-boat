#pragma once
#include "pch.h"

class Codec
{
public:
	Codec();

private:
	const AVCodec* _codec = nullptr;
};

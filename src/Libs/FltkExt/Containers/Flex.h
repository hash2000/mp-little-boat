#pragma once
#include "Libs/FltkExt/Containers/Container.h"

class Flex : public Container
{
public:

	Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position = PushPosition::Start);

	int spacing() const;

	void spacing(int size);

private:
	void AdjustLayout(int cx, int cy, int cw, int ch) override;

private:
	int _spacing = 0;
};


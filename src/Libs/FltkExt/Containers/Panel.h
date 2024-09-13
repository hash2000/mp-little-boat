#pragma once
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/Flex.h"

enum class Docking
{
	Left,
	Top,
	Right,
	Bottom,
	Center,
};

class Panel : public Flex
{
public:
	Panel(int cx, int cy, int cw, int ch, const char* l, Docking docking);

protected:
	void resize(int cx, int cy, int cw, int ch) override;
};

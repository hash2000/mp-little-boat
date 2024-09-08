#pragma once
#include "Libs/FltkExt/Containers/Container.h"

enum class Docking
{
	Left,
	Top,
	Right,
	Bottom,
	Center,
};

class Panel : public Container
{
public:
	Panel(int cx, int cy, int cw, int ch, Docking docking);

	void draw() override;

private:
	void AdjustLayout(int cx, int cy, int cw, int ch) override;

private:
	Docking _docking;
};

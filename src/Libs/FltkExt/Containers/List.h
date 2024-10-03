#pragma once
#include <FL/Fl.H>
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"


class List : public Container
{
public:
	List(int cx, int cy, int cw, int ch);

private:

	void AdjustLayout(int cx, int cy, int cw, int ch) override;

};

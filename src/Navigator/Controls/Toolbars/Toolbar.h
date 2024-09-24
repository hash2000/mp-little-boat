#pragma once

#include <string>
#include <FL/Fl_Button.H>
#include "Libs/FltkExt/Containers/Flex.h"

class Toolbar : public Flex
{
public:
	Toolbar(int cx, int cy, int cw, int ch);

private:

	Fl_Button _fileNew{ 0, 0, 40, 40 };
};

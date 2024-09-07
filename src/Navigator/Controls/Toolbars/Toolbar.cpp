#include <pch.h>
#include "Toolbar.h"
#include "Resources/Icons.h"


Toolbar::Toolbar(int cx, int cy, int cw, int ch)
	: Flex(cx, cy, cw, ch, Flex::Direction::Horz, Flex::PushPosition::Start)
{
	box(FL_FREE_BOXTYPE);
	_fileNew.image(_RC_PicNew);

	begin();
}



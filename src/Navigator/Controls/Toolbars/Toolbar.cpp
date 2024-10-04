#include <pch.h>
#include "Toolbar.h"
#include "Resources/Icons.h"

using Direction = FltkExt::Containers::Direction;
using PushPosition = FltkExt::Containers::PushPosition;
using Flex = FltkExt::Containers::Flex;

Toolbar::Toolbar(int cx, int cy, int cw, int ch)
	: Flex(cx, cy, cw, ch, Direction::Horz, PushPosition::Start)
{
	_fileNew.image(_RC_PicNew);

}



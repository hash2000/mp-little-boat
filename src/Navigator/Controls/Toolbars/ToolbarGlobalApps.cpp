#include <pch.h>
#include "ToolbarGlobalApps.h"
#include "Resources/Icons.h"

ToolbarGlobalApps::ToolbarGlobalApps()
	: Toolbar(ToolbarPosition::Left, 40)
{
	_toolNew.image(&_resource_PicNew);
}

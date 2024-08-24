#include <pch.h>
#include "ToolbarGlobalApps.h"
#include "Resources/Icons.h"

ToolbarGlobalApps::ToolbarGlobalApps()
	: Toolbar(ToolbarPosition::Left)
{
	_toolNew.image(&_resource_PicNew);
}

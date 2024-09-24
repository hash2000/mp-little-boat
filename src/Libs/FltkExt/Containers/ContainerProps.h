#pragma once

enum class Direction : int {
	Vert = 1,
	Horz = 2,
};

enum class PushPosition : int {
	Start,
	End,
};

enum class LayoutStrategy : int {
	ByDirection,
	ByDirectionReflected,
	Full,
};

enum class Docking
{
	Left,
	Top,
	Right,
	Bottom,
	Center,
};

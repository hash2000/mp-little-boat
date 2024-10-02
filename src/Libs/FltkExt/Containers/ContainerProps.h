#pragma once

enum class Direction {
	Vert = 1,
	Horz = 2,
};

enum class PushPosition {
	Start,
	End,
};

enum class LayoutStrategy {
	ByDirection,
	ByDirectionReflected,
	Full,
};

enum class Docking {
	Left,
	Top,
	Right,
	Bottom,
	Center,
};

struct Alignment {
	using Type = unsigned char;

	static const Type Fill = 0;
	static const Type Left = 1<<0;
	static const Type Top = 1<<1;
	static const Type Right = 1<<2;
	static const Type Bottom = 1<<3;
	static const Type Horizontal = 1<<4;
	static const Type Vertical = 1<<5;
	static const Type Center = 1<<6;
	static const Type TopLeft = Top | Left;
	static const Type TopRight = Top | Right;
	static const Type BottomLeft = Bottom | Left;
	static const Type BottomRight = Bottom | Right;
};

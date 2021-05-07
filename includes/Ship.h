#pragma once

struct Ship
{
	size_t X;
	size_t Y;
	short Length;
	short HP;
	short Direction;

	Ship(size_t x, size_t y, short len, short dir) : X(x), Y(y), Length(len), Direction(dir), HP(len)
	{

	}
};

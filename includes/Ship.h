#pragma once

struct Ship
{
	const size_t X;
	const size_t Y;
	const short Length;
	short HP;
	const short Direction;

	Ship(size_t x, size_t y, short len, short dir) : X(x), Y(y), Length(len), Direction(dir), HP(len)
	{

	}
};

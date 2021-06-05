#pragma once

struct Ship
{
	const uint8_t X;
	const uint8_t Y;
	const uint8_t Length;
	uint8_t HP;
	const uint8_t Direction;

	Ship(uint8_t x, uint8_t y, uint8_t len, uint8_t dir) : X(x), Y(y), Length(len), Direction(dir), HP(len)
	{

	}
};

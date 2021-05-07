#pragma once
#include "Global.h"
#include "Ship.h"

struct Cell
{
	static const char Empty = ' ';
	static const char Miss = 'O';
	static const char ShipCell = 'K';
	static const char DamagedShip = 'D';
	static const char DestroyedShip = 'X';

	char Data;
	shared_ptr<Ship> Ship = nullptr;
	int Weight;

	friend ostream& operator << (ostream& out, const Cell& value)
	{
		switch (value.Data)
		{
		case Cell::DestroyedShip:
			out << "\x1B[91m" << value.Data << "\033[0m";
			break;
		case Cell::ShipCell:
			out << "\x1B[33m" << value.Data << "\033[0m";
			break;
		case Cell::DamagedShip:
			out << "\x1B[91m" << value.Data << "\033[0m";
			break;
		default:
			out << value.Data;
			break;
		}
		return out;
	}
};

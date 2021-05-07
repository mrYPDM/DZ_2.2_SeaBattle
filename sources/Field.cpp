#include "../includes/Field.h"

Field::Field()
{
	Map.resize(Size);
	for (int i = 0; i < Size; i++)
	{
		Map.at(i).resize(Size, { Cell::Empty, nullptr, 1 });
	}
}

vector<Cell>& Field::operator[](size_t index)
{
	return Map.at(index);
}

vector<Cell>& Field::at(size_t index)
{
	if (index > Size)
		throw out_of_range("Field_At out_of_range, index = " + to_string(index));
	return Map.at(index);
}

void Field::AddShip(shared_ptr<Ship> ship)
{
	if (ship == nullptr)
		throw "ship is null";

	if (IfShipFits(ship))
	{
		if (ship->Direction == 0)
		{
			for (int x = ship->X; x < ship->X + ship->Length; x++)
			{
				Map.at(x).at(ship->Y).Data = Cell::ShipCell;
				Map.at(x).at(ship->Y).Ship = ship;
			}
		}
		else
		{
			for (int y = ship->Y; y < ship->Y + ship->Length; y++)
			{
				Map.at(ship->X).at(y).Data = Cell::ShipCell;
				Map.at(ship->X).at(y).Ship = ship;
			}
		}
	}
	else throw "Ship can not be placed here";
}

bool Field::IfShipFits(shared_ptr<Ship> ship)
{
	if (ship == nullptr)
		return false;

	// 0 - down / 1 - right
	if (ship->X > Size || ship->Y > Size) // Если голова за пределами поля
		return false;
	if (ship->Direction == 0)
	{
		if (ship->X + ship->Length > Size) // Если тело выходит за пределы
			return false;
		int x_st = ship->X - 1; if (x_st < 0) x_st = 0;
		int x_en = ship->X + ship->Length + 1; if (x_en > Size) x_en--;
		int y_st = ship->Y - 1; if (y_st < 0) y_st = 0;
		int y_en = ship->Y + 2; if (y_en > Size) y_en--;
		for (int x = x_st; x < x_en; x++)
		{
			for (int y = y_st; y < y_en; y++)
			{
				if (Map.at(x).at(y).Data == Cell::ShipCell)
					return false;
			}
		}
	}
	else if (ship->Direction == 1)
	{
		if (ship->Y + ship->Length > Size)
			return false;
		int x_st = ship->X - 1; if (x_st < 0) x_st = 0;
		int x_en = ship->X + 2; if (x_en > Size) x_en--;
		int y_st = ship->Y - 1; if (y_st < 0) y_st = 0;
		int y_en = ship->Y + ship->Length + 1; if (y_en > Size) y_en--;
		for (int x = x_st; x < x_en; x++)
		{
			for (int y = y_st; y < y_en; y++)
			{
				if (Map.at(x).at(y).Data == Cell::ShipCell)
					return false;
			}
		}
	}
	else throw "Direction must be 0 (Down) or 1 (Right)";
	return true;
}

void Field::MarkShipAsDead(shared_ptr<Ship> ship)
{
	if (ship == nullptr)
		return;
	if (ship->Direction == 0)
	{
		int x_st = ship->X - 1; if (x_st < 0) x_st = 0;
		int x_en = ship->X + ship->Length + 1; if (x_en > Size) x_en = Size;
		int y_st = ship->Y - 1; if (y_st < 0) y_st = 0;
		int y_en = ship->Y + 2; if (y_en > Size) y_en = Size;
		for (int x = x_st; x < x_en; x++)
		{
			for (int y = y_st; y < y_en; y++)
			{
				if (Map.at(x).at(y).Data == Cell::DamagedShip)
					Map.at(x).at(y).Data = Cell::DestroyedShip;
				else
					Map.at(x).at(y).Data = Cell::Miss;
			}
		}
	}
	else
	{
		int x_st = ship->X - 1; if (x_st < 0) x_st = 0;
		int x_en = ship->X + 2; if (x_en > Size) x_en = Size;
		int y_st = ship->Y - 1; if (y_st < 0) y_st = 0;
		int y_en = ship->Y + ship->Length + 1; if (y_en > Size) y_en = Size;
		for (int x = x_st; x < x_en; x++)
		{
			for (int y = y_st; y < y_en; y++)
			{
				if (Map.at(x).at(y).Data == Cell::DamagedShip)
				{
					Map.at(x).at(y).Data = Cell::DestroyedShip;
				}
				else
					Map.at(x).at(y).Data = Cell::Miss;
			}
		}
	}
}

void Field::Clear()
{
	Map.clear();
	Map.resize(Size);
	for (int i = 0; i < Size; i++)
	{
		Map.at(i).resize(Size, { Cell::Empty, nullptr, 1 });
	}
}

void Field::CalcWeight(vector<int> availableSizes)
{
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			Map.at(x).at(y).Weight = 1;
		}
	}

	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (Map.at(x).at(y).Data == Cell::DamagedShip)
			{
				Map.at(x).at(y).Weight = 0;
				if (x - 1 >= 0)
				{
					if (y - 1 >= 0)
						Map.at(x - 1).at(y - 1).Weight = 0;
					if (y + 1 < Size)
						Map.at(x - 1).at(y + 1).Weight = 0;
					Map.at(x - 1).at(y).Weight *= 50;
				}
				if (y - 1 >= 0)
					Map.at(x).at(y - 1).Weight *= 50;
				if (y + 1 < Size)
					Map.at(x).at(y + 1).Weight *= 50;
				if (x + 1 < Size)
				{
					if (y - 1 >= 0)
						Map.at(x + 1).at(y - 1).Weight = 0;
					if (y + 1 < Size)
						Map.at(x + 1).at(y + 1).Weight = 0;
					Map.at(x + 1).at(y).Weight *= 50;
				}
			}
		}
	}

	for (int i = 0; i < availableSizes.size(); i++)
	{
		for (int x = 0; x < Size; x++)
		{
			for (int y = 0; y < Size; y++)
			{
				if (Map.at(x).at(y).Data == Cell::DamagedShip || Map.at(x).at(y).Data == Cell::DestroyedShip || Map.at(x).at(y).Data == Cell::Miss || Map.at(x).at(y).Weight == 0)
				{
					Map.at(x).at(y).Weight = 0;
					continue;
				}
				for (int r = 0; r < 2; r++)
				{
					if (IfShipFits(shared_ptr<Ship>(new Ship(x, y, availableSizes[i], r))))
						Map.at(x).at(y).Weight++;
				}
			}
		}
	}
}

vector<pair<int, int>> Field::GetMaxCells()
{
	vector<pair<int, int>> ans;
	int maxweight = 0;
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (Map.at(x).at(y).Weight > maxweight)
			{
				maxweight = Map.at(x).at(y).Weight;
				ans.clear();
				ans.push_back({ x, y });
			}
			else if (Map.at(x).at(y).Weight == maxweight)
			{
				ans.push_back({ x, y });
			}
		}
	}
	return ans;
}

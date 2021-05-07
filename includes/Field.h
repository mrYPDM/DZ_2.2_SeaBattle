#pragma once
#include "Cell.h"

class Field
{
	vector<vector<Cell>> Map;

public:

	Field();

	vector<Cell>& operator[](size_t index);

	vector<Cell>& at(size_t index);

	void AddShip(shared_ptr<Ship> ship);

	bool IfShipFits(shared_ptr<Ship> ship);

	void MarkShipAsDead(shared_ptr<Ship> ship);

	void Clear();

	void CalcWeight(vector<int> availableSizes);

	vector<pair<int, int>> GetMaxCells();
};



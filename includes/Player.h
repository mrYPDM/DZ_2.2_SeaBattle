#pragma once
#include "Field.h"

enum class HitStatus { Miss, Hit, Kill };

class Player
{
	string Name;
	Field MainField;
	Field EnemyField;
	bool AI;
	vector<shared_ptr<Ship>> Ships;
	map<int, int> ShipRules =
	{
		{1, 4},
		{2, 3},
		{3, 2},
		{4, 1}
	};

public:

	Player(string name, bool ai = false);

	~Player();

	void PrintMap();

	void AddShip(shared_ptr<Ship> ship);

	HitStatus Shot(Player* target, int x, int y);

	int ShipsCount();

	HitStatus ReceiveShot(int x, int y);

	void ClearField();

	bool IsAI();

	string GetName();

	vector<pair<int, int>> GetMaxCells();
};

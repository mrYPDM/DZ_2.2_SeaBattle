#include "../includes/Player.h"

Player::Player(string name, bool ai) : Name(name), AI(ai)
{

}

Player::~Player()
{
	ClearField();
}

void Player::ClearField()
{
	Ships.clear();
	this->ShipRules[1] = 4;
	this->ShipRules[2] = 3;
	this->ShipRules[3] = 2;
	this->ShipRules[4] = 1;
	MainField.Clear();
	EnemyField.Clear();
}

void Player::PrintMap()
{
	cout << string((29 - Name.size()) / 2, ' ') << Name << endl;
	cout << setw(29) << cout.fill('#') << endl;
	cout << "  " << Letters << "\t" << "  " << Letters << "\n";
	for (int i = 0; i < Size; i++)
	{
		cout << i << " ";
		for (int j = 0; j < Size; j++)
		{
			cout << MainField.at(i).at(j);
		}
		cout << "\t" << i << " ";
		for (int j = 0; j < Size; j++)
		{
			cout << EnemyField.at(i).at(j);
		}
		cout << endl;
	}
	cout << endl;
}

bool Player::IsAI()
{
	return AI;
}

string Player::GetName()
{
	return Name;
}

int Player::ShipsCount()
{
	return Ships.size();
}

void Player::AddShip(shared_ptr<Ship> ship)
{
	if (ship == nullptr)
		throw "ship in null";

	if (this->ShipRules[ship->Length] == 0)
		throw "There is too much ships with this length";

	MainField.AddShip(ship);
	Ships.push_back(ship);
	this->ShipRules[ship->Length]--;
}

HitStatus Player::Shot(Player* target, int x, int y)
{
	if (x > Size || y > Size || x < 0 || y < 0)
		throw "The target is not on the battlefield";

	auto res = target->ReceiveShot(x, y);
	if (res == HitStatus::Miss)
	{
		EnemyField.at(x).at(y).Data = Cell::Miss;
	}
	else if (res == HitStatus::Hit)
	{
		EnemyField.at(x).at(y).Data = Cell::DamagedShip;
	}
	else
	{
		EnemyField.at(x).at(y).Data = Cell::DamagedShip;
		auto ship = target->MainField.at(x).at(y).Ship;
		EnemyField.MarkShipAsDead(ship);
	}
	return res;
}

HitStatus Player::ReceiveShot(int x, int y)
{
	if (MainField.at(x).at(y).Data == Cell::Empty || MainField.at(x).at(y).Data == Cell::Miss)
	{
		MainField.at(x).at(y).Data = Cell::Miss;
		return HitStatus::Miss;
	}
	else if (MainField.at(x).at(y).Data == Cell::ShipCell)
	{
		auto ship = MainField.at(x).at(y).Ship;

		ship.get()->HP--;
		MainField.at(x).at(y).Data = Cell::DamagedShip;
		if (ship->HP == 0)
		{
			MainField.MarkShipAsDead(ship);
			Ships.erase(remove(Ships.begin(), Ships.end(), ship), Ships.end());
			return HitStatus::Kill;
		}
		else
		{
			return HitStatus::Hit;
		}
	}
}

vector<pair<int, int>> Player::GetMaxCells()
{
	vector<int> sizes;
	for (auto i : Ships)
		sizes.push_back(i->Length);
	EnemyField.CalcWeight(sizes);
	return EnemyField.GetMaxCells();
}

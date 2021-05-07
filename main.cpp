#include "includes/Player.h"

int main()
{
	setlocale(LC_ALL, "");
	srand(time(0));

	vector<Player*> player = { new Player("Player"), new Player("AI", true)};
	int c = 0;

	bool started = false;

	string str = "";

	while (true)
	{
		if (!player[c]->IsAI())
		{
			player[c]->PrintMap();
			cout << endl << "> ";
		}
		else if (player[(c + 1) % player.size()]->IsAI())
		{
			player[0]->PrintMap();
			player[1]->PrintMap();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		else if (started)
		{
			player[(c + 1) % player.size()]->PrintMap();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		if (started && player[(c + 1) % player.size()]->ShipsCount() == 0)
		{
			system("cls");
			cout << "\x1B[33m" << string((29 - player[c]->GetName().size() - 6) / 2, ' ') << player[c]->GetName() << " wins!" << "\033[0m\n";
			player[c]->PrintMap();
			player[(c + 1) % player.size()]->PrintMap();
			system("pause && cls");
			started = false;
			player[c]->ClearField();
			player[(c + 1) % player.size()]->ClearField();
			player[c]->PrintMap();
			cout << "> ";
		}

		try
		{
			if (!player[c]->IsAI()) getline(cin, str);
			else
			{
				if (player[c]->ShipsCount() != 10 && !started)
					str = "ship auto";
				if (player[c]->ShipsCount() == 10 && player[(c + 1) % player.size()]->ShipsCount() == 10 && !started && player[(c + 1) % player.size()]->IsAI())
				{
					system("pause");
					str = "start";
				}
				if (started)
				{
					auto cells = player[c]->GetMaxCells();
					int index = rand() % cells.size();
					str = string(1, char(cells.at(index).second + 65)) + to_string(cells.at(index).first);
				}
			}
			auto data = Split(str);
			if (data.empty()) continue;
			// ship cell len r // ship A0 4 0 
			// ship auto
			if (data[0] == "ship" && !started)
			{
				if (data[1] == "auto")
				{
					player[c]->ClearField();
					int retry = 30;
					for (int i = 0; i < 10; i++)
					{
						try
						{
							int x = rand() % 10;
							int y = rand() % 10;
							int r = rand() % 2;
							player[c]->AddShip(shared_ptr<Ship>(new Ship(x, y, ShipRules[i], r)));
						}
						catch (...)
						{
							i--;
							retry--;
							if (retry == 0)
							{
								player[c]->ClearField();
								retry = 30;
								i = -1;
							}
						}
					}
				}
				else
				{
					int y = data[1][0] - 65;
					int x = stoi(string(1, data[1][1]));
					int l = stoi(data[2]);
					int r = stoi(data[3]);
					player[c]->AddShip(shared_ptr<Ship>(new Ship(x, y, l, r)));
				}
			}
			// start game
			else if (data[0] == "start" && !started)
			{
				if (player[c]->ShipsCount() == 10 && player[(c + 1) % player.size()]->ShipsCount() == 10)
				{
					started = true;
					system("cls");
					continue;
				}
				else
				{
					throw "There is not enough ships";
				}
			}
			// clear
			else if (data[0] == "clear" && !started)
			{
				player[c]->ClearField();
			}
			// help
			else if (data[0] == "help")
			{
				cout << "ship <CELL> <LEN> <ROT> - Добавить корабль с головой в клетке CELL длиной LEN в напралвении ROT (возможно, если игра не начата)"
					<< endl << "\tCELL - Буква и Цифра (ex: A0)"
					<< endl << "\tLEN - Длина от 1 до 4"
					<< endl << "\tROT - направление, 0 - вниз, 1 - вправо" << endl << endl;
				cout << "ship auto - Автоматическая расстановка кораблей (возможно, если игра не начата)" << endl;
				cout << "start - Начать игру (возможно, если кол-во кораблей у обоих игроков равно 10)" << endl;
				cout << "clear - Отчистить поле от кораблей (возможно, если игра не начата)" << endl;
				cout << "<CELL> - Выстрелить по CELL (возможно, если игра начата)" << endl;
				cout << "stop - Остановить игру" << endl;
				cout << "exit - Выйти из игры" << endl;
				system("pause && cls");
				continue;

			}
			// exit
			else if (data[0] == "exit")
			{
				delete player[c];
				delete player[(c + 1) % player.size()];
				break;
			}
			// stop
			else if (data[0] == "stop")
			{
				started = false;
				player[c]->ClearField();
				player[(c + 1) % player.size()]->ClearField();
				system("cls");
				continue;
			}
			// cell
			else if (started)
			{
				int y = data[0][0] - 65;
				int x = stoi(string(1, data[0][1]));
				auto res = player[c]->Shot(player[(c + 1) % player.size()], x, y);
				if (res != HitStatus::Miss)
				{
					system("cls");
					continue;
				}
			}
			c = (c + 1) % player.size();
		}
		catch (const char* e)
		{
			cerr << e << endl;
			system("pause");
		}
		catch (exception e)
		{
			cerr << e.what() << endl;
			system("pause");
		}
		system("cls");
	}
}
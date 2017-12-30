#include "gm.h"

GameManager::GameManager()
{
	SMALL_RECT r; // rozmiar i pozycja okna
	r.Left = r.Top = 0;
	r.Right = 80;
	r.Bottom = 40;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);
	player = nullptr;
	gs = GS_MENU;
}


GameManager::~GameManager()
{
	if (player != nullptr)
		delete player;

	for (unsigned i = 0; i < obstacles.size(); i++)
	{
		delete obstacles.at(i);
	}
}

void GameManager::Input()
{
	if (gs == GS_PLAY)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (player->CanJump() == true)
			{
				player->Jump();
			}
		}
	}
}

void GameManager::Render()
{
	if (gs == GS_PLAY)
	{
		player->Render();
		for (unsigned i = 0; i < obstacles.size(); i++)
		{
			obstacles.at(i)->Render();
		}
		COORD pos = { 0, 22 };
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		std::cout << "Wynik: " << player->score << std::endl;
	}
	else if (gs == GS_MENU)
	{
		int tmp = 0;
		while (!(tmp == 1 || tmp == 2))
		{
			system("cls");
			std::cout << "Wcisnij 1 - graj" << std::endl;
			std::cout << "Wcisnij 2 - wyjscie" << std::endl;

			std::cin >> tmp;
		}
		if (tmp == 1) //klawisz 1 menu
		{
			player = new Player();
			system("cls");
			COORD pos = { 0, 21 };
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, pos);
			std::cout << "----------------------------------------------------------------------------";
			gs = GS_PLAY;

		}

		else if (tmp == 2) //klawisz 2 menu
		{
			gs = GS_QUIT;
		}
	}
	else if (gs == GS_END)
	{
		system("cls");
		std::cout << "Zdobyles: " << player->score << " punktow." << std::endl;
		std::cout << "Wcisnij enter, aby kontynuowac..." << std::endl;
		delete player;
		player = nullptr;
		for (unsigned i = 0; i < obstacles.size(); i++)
		{
			delete obstacles.at(i);
		}
		obstacles.clear();
		while (!(GetKeyState(VK_RETURN) & 0x8000)) {}
		gs = GS_MENU;
	}
}

void GameManager::Update()
{
	if (gs == GS_PLAY)
	{
		player->Update();
		std::random_device rd;
		if (obstacles.size() < 1)
		{
			GenerateObstacle();
		}
		else if (80 - obstacles.at(obstacles.size() - 1)->x > MIN_SPACE_BETWEEN)
		{
			if (rd() % 100 + 1 < 15) // % szans na stworzenie nowej przeszkody
			{
				GenerateObstacle();
			}
		}
		for (unsigned i = 0; i < obstacles.size(); i++)
		{
			obstacles.at(i)->Update();
		}
		for (unsigned i = 0; i < obstacles.size(); i++)
		{
			for (int j = 0; j < obstacles.at(i)->h; j++)
			{
				if (obstacles.at(i)->x == player->x && player->y == obstacles.at(i)->y - j) // kolizja z przeszkoda
				{
					gs = GS_END;
					break;
				}
			}
			if (obstacles.at(i)->x <= 0)
			{
				delete obstacles.at(i);
				obstacles.erase(obstacles.begin() + i);
			}
		}
	}
}

void GameManager::PreRender()
{
	if (gs == GS_PLAY)
	{
		player->PreRender();
		for (unsigned i = 0; i < obstacles.size(); i++)
		{
			obstacles.at(i)->PreRender();
		}
	}
}

void GameManager::GenerateObstacle()
{
	std::random_device rd;
	obstacles.push_back(new Obstacle(80, 20, rd() % 4));
}

#pragma once

#include "pl.h"
#include "pr.h"
#include <vector>
#include <random>

enum GAMESTATE
{
	GS_MENU = 0,
	GS_PLAY = 1,
	GS_END = 2,
	GS_QUIT = 4
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	GAMESTATE gs;
	Player* player;
	std::vector <Obstacle*> obstacles;
	int MIN_SPACE_BETWEEN = 8;

	void Input();
	void Render();
	void Update();
	void PreRender();
	void GenerateObstacle();
};


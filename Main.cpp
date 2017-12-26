#pragma once

#include <Windows.h>
#include <iostream>

enum PlayerState
{
	STAYING = 0,
	JUMPING = 1,
	FALLING = 2
};

class Player
{
public:
	int x, y, score;
	PlayerState state;

	int BASE_HEIGHT = 20;
	int MAX_JUMP_HEIGHT = (BASE_HEIGHT - 5);

	Player();
	~Player();

	void Render();
	void Update();
	void PreRender();
	void Jump();
	bool CanJump();

};


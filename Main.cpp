#include "Nag³ówek1.h"



Player::Player()
	:x(4), y(20), state(STAYING), score(0)
{
}


Player::~Player()
{
}

void Player::Render()
{
	COORD pos = { x, y };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	std::cout << "@";
}

void Player::Update()
{
	score++;
	if (state == JUMPING)
	{
		if (y > MAX_JUMP_HEIGHT)
		{
			y--;
		}
		else
		{
			state = FALLING;
		}
	}
	else if (state == FALLING)
	{
		if (y < BASE_HEIGHT)
			y++;
		else
			state = STAYING;
	}
}

void Player::PreRender()
{
	COORD pos = { x, y };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	std::cout << " ";
}

void Player::Jump()
{
	state = JUMPING;
}

bool Player::CanJump()
{
	if (y == BASE_HEIGHT)
		return true;
	return false;
}
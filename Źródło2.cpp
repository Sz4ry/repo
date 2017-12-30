#include "pr.h"



Obstacle::Obstacle(int x, int y, int h)
	:x(x), y(y), h(h)
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::PreRender()
{
	for (int j = 0; j < h; j++)
	{
		COORD pos = { x, y - j };
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		std::cout << " ";
	}
}

void Obstacle::Render()
{
	for (int j = 0; j < h; j++)
	{
		COORD pos = { x, y - j };
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		std::cout << "|";
	}

}


void Obstacle::Update()
{
	x--;
}

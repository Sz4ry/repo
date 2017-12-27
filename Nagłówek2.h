#pragma once

#include <Windows.h>
#include <iostream>

class Obstacle
{
public:
	int x, y, h;
	Obstacle(int x, int y, int h);
	~Obstacle();

	void PreRender();
	void Render();
	void Update();
}


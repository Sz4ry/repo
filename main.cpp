#include "gm.h"
#include <ctime>
#include <conio.h>

int main()
{
	GameManager man;
	clock_t start = clock();
	while (man.gs != GS_QUIT)
	{
		if ((clock() - start) > CLOCKS_PER_SEC / 8) // predkosc gry
		{
			start = clock();
			man.Input();
			man.PreRender();
			man.Update();
			man.Render();
		}
	}
}
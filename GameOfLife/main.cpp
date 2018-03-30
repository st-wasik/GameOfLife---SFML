#include "GameOfLife.h"



int WinMain()
{
	GameOfLife game;
	game.setRule("238/357");
	game.run();
}
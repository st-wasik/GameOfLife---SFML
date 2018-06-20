#include "GameOfLife.h"



int WinMain()
{
	GameOfLife game;
	//game.setRule("5678/35678");//ameba
	game.setRule("12345/3");//labirynt
	//game.setRule("23/3");
	//game.setRule("1234567/1234567");//wiadomosc od obcych
	game.run();
}
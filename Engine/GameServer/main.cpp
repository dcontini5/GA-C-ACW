// GameServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ServersideGame.h"
#include "Window.h"


int main()
{

	ServersideGame game;

	std::shared_ptr<Window> win = nullptr;
	
	game.Initialize(win);


	return 0;
	
}

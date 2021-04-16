// GameServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ServersideGame.h"


int main()
{

	ServersideGame game;

	//std::shared_ptr<Window> win = nullptr;
	
	game.Initialize();

	while (game.GetQuitFlag()) {
			
	}
	
	
	return 0;
	
}

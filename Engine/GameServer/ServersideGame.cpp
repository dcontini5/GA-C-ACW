#include "ServersideGame.h"
#include "ServersideScene.h"

void ServersideGame::Initialize(std::shared_ptr<Window>& pWindow){

	Game::Initialize(pWindow);
	
	mScene = std::make_shared<ServersideScene>();

	mScene->Start();

	
}

void ServersideGame::Initialize(){

	
	mScene = std::make_shared<ServersideScene>();

	mScene->Start();

	
}

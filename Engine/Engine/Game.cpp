#include "Game.h"

#include "Message.h"
#include "Scene.h"

Game* Game::mInstance = nullptr;

void Game::OnMessage(std::shared_ptr<Message>& pMessage){
	
	if (pMessage->GetType() == MessageTypes::ADDED_COMPONENT) mScene->OnMessage(pMessage);

	
}

void Game::Initialize(std::shared_ptr<Renderer>& pRenderer){




	
}

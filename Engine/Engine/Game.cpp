#include "Game.h"

#include "Message.h"
#include "Scene.h"
#include "InputStateMessage.h"

Game* Game::mInstance = nullptr;

void Game::BroadcastMessage(std::shared_ptr<Message>& pMessage){
	
	//if (pMessage->GetType() == MessageTypes::ADDED_COMPONENT) 
	mScene->OnMessage(pMessage);

	
}

void Game::OnKeyboard(const InputState& pState){

	std::shared_ptr<Message> msg = std::make_shared<InputStateMessage>(pState);

	BroadcastMessage(msg);
	
}

//void Game::SetActiveCamera(const std::shared_ptr<GameObject>& pCamera){
//
//	mWindow->GetRenderer()->SetCamera(pCamera);
//	
//}

void Game::Initialize(std::shared_ptr<Window>& pWindow){

	mWindow = pWindow;
	
}

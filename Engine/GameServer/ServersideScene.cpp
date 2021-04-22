#include "ServersideScene.h"

#include "PyramidServer.h"
#include "NewPlayerConnectedMessage.h"


#include "CollisionSystem.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "ThreadManager.h"

void ServersideScene::Start(){


	//std::shared_ptr<System> physicsSystem = std::make_shared<PhysicsSystem>();
	//std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>();
	//
	//AddSystem(physicsSystem);
	//AddSystem(collisionSystem);
	std::shared_ptr<System> server = std::make_shared<PyramidServer>();
	AddSystem(server);

	Scene::Start();

	
}

void ServersideScene::OnMessage(std::shared_ptr<Message>& pMessage){

	Scene::OnMessage(pMessage);

	switch (pMessage->GetType()) {


		case MessageTypes::PLAYER_CONNECTED:
		{
			const auto playerConnectedMessage = std::reinterpret_pointer_cast<NewPlayerConnectedMessage>(pMessage);

			auto player = std::make_shared<GameObject>();
			player->InitPos({ 0.f, 0.f, 0.f });
			player->setRot({ 0.f, 0.f, 0.f });
		
		
			mGameObjectList.push_back(player);

			playerConnectedMessage->GetTransferSocket()->SetClient(player);
			
			//todo implement: this might work
				//server::register_player(gameObject) { add passed component to players map ip + game object }

				//start threading here
				//when player coords are needed transfer sockets has the needed ip to be able to fetch the player form the player list
				//if this work omg

			//ThreadManager::Instance()->AddThreadWithArgs(/*pyramidclient::send(), &server, playerConnectedMessage->GetTransferSocket()*/);

			break;
		}



	}

	
}


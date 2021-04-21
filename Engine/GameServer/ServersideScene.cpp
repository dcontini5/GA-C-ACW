#include "ServersideScene.h"


#include "NetworkingSystem.h"
#include "CollisionSystem.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "NewPlayerConnectedMessage.h"
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



	

	
	auto sphereObj = std::make_shared<GameObject>();
	
	sphereObj->SetPos({ 0, 5, -15 });
	sphereObj->setRot({ 0, 0, 0 });
	sphereObj->setScale({ 1, 1, 1 });

	{

	

	}


	mGameObjectList.push_back(sphereObj);

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

			playerConnectedMessage->GetTransferSocket()->SetPlayerGameObject(player);

			mGameObjectList.push_back(player);

			//ThreadManager::Instance()->AddThreadWithArgs(/*pyramidclient::send(), &server, playerConnectedMessage->GetTransferSocket()*/);
			break;
		}



	}

	
}


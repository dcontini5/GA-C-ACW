#include "ServersideScene.h"

#include "PyramidServer.h"
#include "PlayerConnectedMessage.h"
#include "NetworkComponent.h"

#include "CollisionSystem.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
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

	int noOfLevels = 1;

	for (auto i = noOfLevels; i > 0; i--) {

		auto x = 0;
		x -= i - 1;
		const auto z = x;

		for (auto j = i - 1; j >= 0; j--) {

			for (auto k = i - 1; k >= 0; k--) {

				auto sphereObj = std::make_shared<GameObject>();

				sphereObj->InitPos({ x + k * 2, (noOfLevels - i) * 1.45 + 1, z + j * 2 - 5.f });
				sphereObj->setRot({ 0, 0, 0 });
				sphereObj->setScale({ 1.f, 1.f, 1.f });

				{

					auto rc = std::make_shared<NetworkComponent>(sphereObj);

					auto comp = std::dynamic_pointer_cast<GameObjectComponent>(rc);

					sphereObj->AddComponent(comp);
										
				}


				mGameObjectList.push_back(sphereObj);


			}


		}


	}

	
}

void ServersideScene::OnMessage(std::shared_ptr<Message>& pMessage){

	Scene::OnMessage(pMessage);

	switch (pMessage->GetType()) {


		case MessageTypes::PLAYER_CONNECTED:
		{
			const auto playerConnectedMessage = std::reinterpret_pointer_cast<PlayerConnectedMessage>(pMessage);

			auto player = std::make_shared<GameObject>();
			player->InitPos({ 0.f, 0.f, 0.f });
			player->setRot({ 0.f, 0.f, 0.f });
		
			mGameObjectList.push_back(player);

			playerConnectedMessage->GetTransferSocket()->SetClient(player);

			break;
		}



	}

	
}


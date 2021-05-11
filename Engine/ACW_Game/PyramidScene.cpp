#include "PyramidClient.h"

#include "NetworkComponent.h"

#include "PyramidScene.h"
#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Game.h"
#include "InfinitePlaneCollisionComponent.h"
#include "InputKeys.h"
#include "SphereCollisionComponent.h"
#include "ThreadManager.h"
#include "ResetSceneMessage.h"
#include "InputStateMessage.h"
#include "PyramidClientMessageTypes.h"
#include "UpdateFrequencyMessage.h"
#include "PyramidPlayerInputComponent.h"
#include "CurrentSystemFrequencyMessage.h"
#include "PyramidCameraComponent.h"
#include "UpdatePyramidHeightMessage.h"
#include "SpawnObjectMessage.h"

void PyramidScene::Start(){

	const auto i = 1;
	
	if (1 == i) {


		auto renderer = Game::Instance()->GetWindow()->GetRenderer();
		std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
		std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(renderer);
		
		std::shared_ptr<System> client = std::make_shared<PyramidClient>();
		client->SetSysFrequency(30);

		
		AddSystem(renderSystem);
		AddSystem(client);

		

		auto planeObj = std::make_shared<GameObject>();



		planeObj->InitPos({ 0.f, 0.f, 0.f });
		planeObj->setRot({ 0.f, 0.f, 0.f });
		planeObj->setScale({ 1.f, 1.f, 1.f });

		{

			auto rc = std::make_shared<RenderComponent>(planeObj);
			auto mesh = ResourceManager::Instance()->GetMesh("Plane");

			rc->SetMesh(mesh);
			rc->StartDrawing();

			auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(rc);

			planeObj->AddComponent(comp);


		}

		mGameObjectList.push_back(planeObj);

		{
			std::shared_ptr<GameObject> player = std::make_shared<GameObject>();

			//player->SetPos({ 0.f, 8.f, 6.f });
			player->SetPos({ 0.f, 4.f, -20.f });
			//player->setRot({ 1.f, 1.f, 1.f });
			
			std::shared_ptr<Observer> obs = std::make_shared<PyramidPlayerInputComponent>(player);

			player->Register(MessageTypes::INPUT_STATE, obs);

			std::shared_ptr<CameraComponent> cc = std::make_shared<PyramidCameraComponent>(player);

			cc->SetForward({ 0.0f, 0.0f, 1.0f });

			obs = std::dynamic_pointer_cast<Observer>(cc);

			player->Register(MessageTypes::CAMERA_UPDATE, obs);

			std::shared_ptr<GameObjectComponent> comp = std::dynamic_pointer_cast<GameObjectComponent>(cc);

			player->AddComponent(comp);
			 
            mPlayer = player;

			renderer->SetCamera(player);
			
		}
		
		Scene::Start();
	}
	
}

void PyramidScene::OnMessage(std::shared_ptr<Message>& pMessage){


	switch (pMessage->GetType()) {

		case MessageTypes::RESET_SCENE:
		{
				auto resetMsg = std::reinterpret_pointer_cast<ResetSceneMessage>(pMessage);
				std::vector<GameObjectPtr> gameObjects(std::move(resetMsg->GetGameObjects()));

				{
					std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
					ThreadManager::Instance()->PauseUnpauseRenderer(true);
					//ThreadManager::Instance()->GetConditionVariable().notify_one();
				
					
				for(auto& go : gameObjects){

					auto rc = std::make_shared<RenderComponent>(go);
					auto mesh = ResourceManager::Instance()->GetMesh("Sphere");

					rc->SetMesh(mesh);
					rc->StartDrawing();

					auto comp = std::dynamic_pointer_cast<GameObjectComponent>(rc);

					go->AddComponent(comp);

					auto nc = std::make_shared<NetworkComponent>(go);

					comp = std::dynamic_pointer_cast<GameObjectComponent>(nc);

					go->AddComponent(comp);

					
				}
				
				
					//std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
					ThreadManager::Instance()->PauseUnpauseRenderer(false);
					ThreadManager::Instance()->GetConditionVariable().notify_one();
				}
				break;
		}
		
		case PyramidClientMessageTypes::UPDATE_FREQUENCY:
		{
			auto ufmsg = std::reinterpret_pointer_cast<UpdateFrequencyMessage>(pMessage);

			auto system = mSystems.find(ufmsg->GetSystemType());
				
			if (system != mSystems.end()) system->second->SetSysFrequency(ufmsg->GetFrequency());

			if (ufmsg->GetSystemType() == SystemTypes::NETWORKING) PyramidGame::GetGameState()->networkTargetFrequency = ufmsg->GetFrequency();
			
			break;
			
		}
		/*
		case PyramidClientMessageTypes::SPAWN_OBJECT:
		{

			auto soMsg = std::reinterpret_pointer_cast<SpawnObjectMessage>(pMessage);
			GameObjectPtr go = std::make_shared<GameObject>();

			go->InitPos(soMsg->GetPos());
			go->setScale(soMsg->GetScale());

			auto rc = std::make_shared<RenderComponent>(go);
			auto mesh = ResourceManager::Instance()->GetMesh("Sphere");

			rc->SetMesh(mesh);
			rc->StartDrawing();

			auto comp = std::dynamic_pointer_cast<GameObjectComponent>(rc);

			go->AddComponent(comp);

			auto nc = std::make_shared<NetworkComponent>(go);

			comp = std::dynamic_pointer_cast<GameObjectComponent>(nc);

			go->AddComponent(comp);
			break;

		}*/
		 
		case MessageTypes::CURRENT_SYSTEM_FREQUENCY:
		{
			auto csfMsg = std::reinterpret_pointer_cast<CurrentSystemFrequencyMessage>(pMessage);

			if (csfMsg->GetSystemType() == SystemTypes::RENDER) PyramidGame::GetGameState()->graphicsActualFrequency = csfMsg->GetFrequency();
			else PyramidGame::GetGameState()->clientActualFrequency = csfMsg->GetFrequency();
			break;
		}

		case PyramidClientMessageTypes::UPDATE_PYRAMID_HEIGHT:
		{
			const auto uphmsg = std::reinterpret_pointer_cast<UpdatePyramidHeightMessage>(pMessage);
			PyramidGame::GetGameState()->pyramidSize = uphmsg->GetHeight();
			break;
				
		}

		 
		default: break;
		
	}
	
	
	Scene::OnMessage(pMessage);

		
}

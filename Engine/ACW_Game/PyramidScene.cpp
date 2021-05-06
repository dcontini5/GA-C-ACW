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
#include "CameraComponent.h"

void PyramidScene::Start(){

	const auto i = 1;
	
	if (1 == i) {


		auto renderer = Game::Instance()->GetWindow()->GetRenderer();
		std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
		std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(renderer);
		
		std::shared_ptr<System> client = std::make_shared<PyramidClient>();

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

			auto cc = std::make_shared<InfinitePlaneCollisionComponent>(planeObj);

			cc->SetNormal({ 0.f, 1.f, 0.f });

			comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

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

			std::shared_ptr<CameraComponent> cc = std::make_shared<CameraComponent>(player);

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
	
	if (1 == i) return;
	auto renderer = Game::Instance()->GetWindow()->GetRenderer();
	
	std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
	std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(renderer);

	std::shared_ptr<System> physicsSystem = std::make_shared<PhysicsSystem>();

	std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>();
	
	
	AddSystem(collisionSystem);
	AddSystem(renderSystem);
	AddSystem(physicsSystem);

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

		auto cc = std::make_shared<InfinitePlaneCollisionComponent>(planeObj);

		cc->SetNormal({ 0.f, 1.f, 0.f });
		
		comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);
			   		
		planeObj->AddComponent(comp);
		
		
	}
		
	mGameObjectList.push_back(planeObj);

	int noOfLevels = 5;

	for (auto i = noOfLevels; i > 0; i--) {

		auto x = 0;
		x -= i - 1;
		const auto z = x;

		for (auto j = i - 1; j >= 0; j--) {

			for (auto k = i - 1; k >= 0; k--) {

				auto sphereObj = std::make_shared<GameObject>();

				sphereObj->InitPos({ x + k * 2, (noOfLevels - i) * 1.45 + 1, z + j * 2 - 5.f});
				sphereObj->setRot({ 0, 0, 0 });
				sphereObj->setScale({ 1.f, 1.f, 1.f });

				{

					auto rc = std::make_shared<RenderComponent>(sphereObj);
					auto mesh = ResourceManager::Instance()->GetMesh("Sphere");

					rc->SetMesh(mesh);
					rc->StartDrawing();

					auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(rc);

					sphereObj->AddComponent(comp);

					auto pc = std::make_shared<PhysicsComponent>(sphereObj);
					pc->SetDrag(0.60f);
					pc->SetStatic(i == noOfLevels);

					comp = std::reinterpret_pointer_cast<GameObjectComponent>(pc);

					sphereObj->AddComponent(comp);

					auto cc = std::make_shared<SphereCollisionComponent>(sphereObj);

					cc->SetRadius(1.f);

					comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

					sphereObj->AddComponent(comp);
				}


				mGameObjectList.push_back(sphereObj);


			}

			
		}

		
	}

	
	Scene::Start();
	
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
				
			break;
			
		}
		 
		case MessageTypes::CURRENT_SYSTEM_FREQUENCY:
		{
			auto csfMsg = std::reinterpret_pointer_cast<CurrentSystemFrequencyMessage>(pMessage);

			if (csfMsg->GetSystemType() == SystemTypes::RENDER) PyramidGame::GetGameState()->graphicsActualFrequency = csfMsg->GetFrequency();

		}
		 
		default: break;
		
	}
	
	
	Scene::OnMessage(pMessage);

		
}

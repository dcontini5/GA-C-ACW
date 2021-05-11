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
#include "PyramidMessageTypes.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "ThreadManager.h"
#include "UpdateFrequencyMessage.h"
#include "UpdatePyramidHeightMessage.h"

void ServersideScene::Start(){


	std::shared_ptr<System> physicsSystem = std::make_shared<PhysicsSystem>();
	std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>();
	std::shared_ptr<System> server = std::make_shared<PyramidServer>();
	
	AddSystem(physicsSystem);
	AddSystem(collisionSystem);
	AddSystem(server);

	auto planeObj = std::make_shared<GameObject>();



	planeObj->InitPos({ 0.f, 0.f, 0.f });
	planeObj->setRot({ 0.f, 0.f, 0.f });
	planeObj->setScale({ 1.f, 1.f, 1.f });

	{

		auto cc = std::make_shared<InfinitePlaneCollisionComponent>(planeObj);

		cc->SetNormal({ 0.f, 1.f, 0.f });

		auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

		planeObj->AddComponent(comp);
	}

	mGameObjectList.push_back(planeObj);
	
	mHeight = ResourceManager::Instance()->GetPyramidHeight();
	CreatePyramid();

	Scene::Start();
	
}

void ServersideScene::OnMessage(std::shared_ptr<Message>& pMessage){

	Scene::OnMessage(pMessage);

	switch (pMessage->GetType()) {

		//case MessageTypes::RESET_SCENE:
		//{
		//
		//	ResetScene();
		//	break;
		//		
		//}
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
		
		case PyramidMessageTypes::UPDATE_FREQUENCY:
		{
			const auto ufmsg = std::reinterpret_pointer_cast<UpdateFrequencyMessage>(pMessage);

			auto system = mSystems.find(ufmsg->GetSystemType());

			if (system != mSystems.end()) system->second->SetSysFrequency(ufmsg->GetFrequency());

			break;

		}

		case PyramidMessageTypes::UPDATE_PYRAMID_HEIGHT:
		{

			const auto uphmsg = std::reinterpret_pointer_cast<UpdatePyramidHeightMessage>(pMessage);

			mHeight = uphmsg->GetHeight();
			ResourceManager::Instance()->SetPyramidHeight(mHeight);
			
			break;
				
		}


	}

	
}

void ServersideScene::ResetScene(){
	
	std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
	ThreadManager::Instance()->PauseUnpausePhysics(true);

	ThreadManager::Instance()->GetConditionVariable().wait(lk, [] {
		return (!ThreadManager::Instance()->IsCollisionsDone());
	});


	std::unique_lock<std::shared_mutex> slk(ThreadManager::Instance()->GetSharedMutex());
	
	while (!mGameObjectList.empty()){

		mGameObjectList.front()->ClearComponents();
		mGameObjectList.erase(mGameObjectList.begin());

	}
	
	CreatePyramid();

	ThreadManager::Instance()->PauseUnpausePhysics(false);
	ThreadManager::Instance()->GetConditionVariable().notify_one();
	
}

void ServersideScene::CreatePyramid(){


	for (auto i = mHeight; i > 0; i--) {

		auto x = 0;
		x -= i - 1;
		const auto z = x;

		for (auto j = i - 1; j >= 0; j--) {

			for (auto k = i - 1; k >= 0; k--) {

				auto sphereObj = std::make_shared<GameObject>();

				sphereObj->InitPos({ x + k * 2, (mHeight - i) * 1.45 + 1, z + j * 2 - 5.f });
				sphereObj->setRot({ 0, 0, 0 });
				sphereObj->setScale({ 1.f, 1.f, 1.f });

				{

					auto nc = std::make_shared<NetworkComponent>(sphereObj);

					auto comp = std::dynamic_pointer_cast<GameObjectComponent>(nc);

					sphereObj->AddComponent(comp);

					auto pc = std::make_shared<PhysicsComponent>(sphereObj);
					pc->SetDrag(0.60f);
					pc->SetStatic(i == mHeight);

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
}


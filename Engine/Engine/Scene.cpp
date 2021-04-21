#include "Scene.h"
#include "System.h"
#include "ThreadManager.h"
#include "AddedComponentMessage.h"
#include "NewPlayerConnectedMessage.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

Scene::~Scene(){

	for(auto threadID : mSystemThreadIDs){

		ThreadManager::Instance()->TeminateThread(threadID.second);
		
	}
	
}

void Scene::OnMessage(std::shared_ptr<Message>& pMessage){

	//if(objRemove) then remove
	switch (pMessage->GetType()){

	case MessageTypes::ADDED_COMPONENT:
		{

			auto addMsg = std::reinterpret_pointer_cast<AddedComponentMessage>(pMessage);

			if (mSystems.find(addMsg->GetCompType()) != mSystems.end()) {

				auto go = addMsg->GetSender();
				mSystems[addMsg->GetCompType()]->AddObject(go);

			}
			break;
		}

	case MessageTypes::PLAYER_CONNECTED:
		{

			auto playerConnectedMessage = std::reinterpret_pointer_cast<NewPlayerConnectedMessage>(pMessage);

			auto player = std::make_shared<GameObject>();
			player->InitPos({ 0.f, 0.f, 0.f });
			player->setRot({ 0.f, 0.f, 0.f });

			playerConnectedMessage->GetTransferSocket()->SetPlayerGameObject(player);

			mGameObjectList.push_back(player);

			
			
		}


		
	}
	
		
	
}

void Scene::Start(){

	auto* const threadManager = ThreadManager::Instance();

	for(const auto& system : mSystems){

		const auto type = system.second->GetType();

		switch (type){

			case SystemTypes::RENDER:
				{
					auto sys = std::reinterpret_pointer_cast<RenderSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&RenderSystem::Start, sys);
					break;
				}
			
			case SystemTypes::COLLISION:
				{
					auto sys = std::reinterpret_pointer_cast<CollisionSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&CollisionSystem::Start, sys);
					break;
				}

			case SystemTypes::PHYSICS:
				{
					auto sys = std::reinterpret_pointer_cast<PhysicsSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&PhysicsSystem::Start, sys);
					break;
				}
			

			//case SystemTypes::NETWORKING:
			//	auto netSys = std::reinterpret_pointer_cast<NetworkingSystem>(system.second);
			//	mSystemThreadIDs[type] = threadManager->AddThread(&NetworkingSystem::Start, netSys);
			
			default:
				break;
			
		}

		
	}

}

void Scene::AddSystem(std::shared_ptr<System>& pSystem){

	if (mSystems.find(pSystem->GetType()) == mSystems.end())
		mSystems[pSystem->GetType()] = pSystem;

}

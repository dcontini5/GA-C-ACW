#include "Scene.h"

#include "Server.h"
#include "System.h"
#include "ThreadManager.h"
#include "AddedComponentMessage.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "InputStateMessage.h"
#include "InputKeys.h"
#include "Game.h"

Scene::~Scene(){

	for(auto threadID : mSystemThreadIDs){

		ThreadManager::Instance()->TeminateThread(threadID.second);
		
	}
	
}

void Scene::OnMessage(std::shared_ptr<Message>& pMessage){

	switch (pMessage->GetType()){

	case MessageTypes::ADDED_COMPONENT:
		{

			auto addMsg = std::reinterpret_pointer_cast<AddedComponentMessage>(pMessage);

			if (mSystems.find(addMsg->GetCompType()) != mSystems.end()) {

				auto go = addMsg->GetSender();
				mSystems[addMsg->GetCompType()]->AddObject(go);

			}
			return;
		}
		
	
	case MessageTypes::REMOVED_COMPONENT:
		{

			auto remMsg = std::reinterpret_pointer_cast<AddedComponentMessage>(pMessage);

			if (mSystems.find(remMsg->GetCompType()) != mSystems.end()) {

				auto go = remMsg->GetSender();
				mSystems[remMsg->GetCompType()]->RemoveObject(go);

			}
			return;
		}

	case MessageTypes::INPUT_STATE:
		{
			
			auto inpMsg = std::reinterpret_pointer_cast<InputStateMessage>(pMessage);

			if (inpMsg->GetInputState().key == ESCAPE){

				Game::Instance()->Quit();
				return;
			}
			
			mPlayer->OnMessage(pMessage);
			return;
		}
		
	default: return;
	}
		
	
}

void Scene::Start(){

	auto* const threadManager = ThreadManager::Instance();

	for(const auto& system : mSystems){

		const auto type = system.second->GetType();

		switch (type){

			case SystemTypes::RENDER:
				{
					auto sys = std::dynamic_pointer_cast<RenderSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&RenderSystem::Start, sys);
					break;
				}
			
			case SystemTypes::COLLISION:
				{
					auto sys = std::dynamic_pointer_cast<CollisionSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&CollisionSystem::Start, sys);
					break;
				}

			case SystemTypes::PHYSICS:
				{
					auto sys = std::dynamic_pointer_cast<PhysicsSystem>(system.second);
					mSystemThreadIDs[type] = threadManager->AddThread(&PhysicsSystem::Start, sys);
					break;
				}
			

			case SystemTypes::NETWORKING:
				{
					auto sys = std::dynamic_pointer_cast<NetworkingSystem>(system.second);
					sys->Init();
					mSystemThreadIDs[type] = threadManager->AddThread(&NetworkingSystem::Start, sys);
					break;
				}
				
			
			default:
				break;
			
		}

		
	}

}

void Scene::AddSystem(std::shared_ptr<System>& pSystem){

	if (mSystems.find(pSystem->GetType()) == mSystems.end())
		mSystems[pSystem->GetType()] = pSystem;

}

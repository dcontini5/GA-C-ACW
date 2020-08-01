#include "Scene.h"
#include "System.h"
#include "ThreadManager.h"
#include "AddedComponentMessage.h"
#include "RenderSystem.h"


Scene::~Scene(){

	for(auto threadID : mSystemThreadIDs){

		ThreadManager::Instance()->TeminateThread(threadID.second);
		
	}
	
}

void Scene::OnMessage(std::shared_ptr<Message>& pMessage){

	//if(objRemove) then remove
	if(pMessage->GetType() == MessageTypes::ADDED_COMPONENT){

		auto addMsg = std::reinterpret_pointer_cast<AddedComponentMessage>(pMessage);

		if (mSystems.find(addMsg->GetCompType()) != mSystems.end()){
			
			auto go = addMsg->GetSender();
			mSystems[addMsg->GetCompType()]->AddObject(go);
			
		}
		
	}

	
}

void Scene::Start(){

	auto* const threadManager = ThreadManager::Instance();

	for(const auto& system : mSystems){

		const auto type = system.second->GetType();
		
		if (system.second->GetType() == SystemTypes::RENDER) {
			
			auto sys = std::reinterpret_pointer_cast<RenderSystem>(system.second);
			mSystemThreadIDs[type] = threadManager->AddThread(&RenderSystem::Start, sys);
			
		}
		
	}

}

void Scene::AddSystem(std::shared_ptr<System>& pSystem){

	if (mSystems.find(pSystem->GetType()) != mSystems.end()) mSystems[pSystem->GetType()] = pSystem;

}

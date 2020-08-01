#include "Scene.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "ThreadManager.h"
#include "AddedComponentMessage.h"


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

void Scene::Start(std::shared_ptr<Renderer>& pRenderer){

	
	
	//std::shared_ptr<RenderSystem> renderSystem = std::make_shared<RenderSystem>();
	//renderSystem->SetRenderer(pRenderer);
	//
	//mSystems[RENDER] = std::make_shared<RenderSystem>();
	//
	//mCollisionSystem = std::shared_ptr<CollisionSystem>();
	//
	//mPhysicsSystem = std::shared_ptr<PhysicsSystem>();
	//
	//const auto threadManager = ThreadManager::Instance();
	//
	//mRenderSystemThreadID = threadManager->AddThread(&RenderSystem::Start, mRenderSystem);
	//mCollisionSystemThreadID = threadManager->AddThread(&CollisionSystem::Start, mCollisionSystem);
	//mPhysicsSystemThreadID = threadManager->AddThread(&PhysicsSystem::Start, mPhysicsSystem);

}

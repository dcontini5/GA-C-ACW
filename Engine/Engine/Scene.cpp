#include "Scene.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "ThreadManager.h"


void Scene::OnMessage(std::shared_ptr<Message>& pMessage){

	//if(objRemove) then remove


	
}

void Scene::Start(std::shared_ptr<Renderer>& pRenderer){

	mRenderSystem = std::make_shared<RenderSystem>();
	mRenderSystem->SetRenderer(pRenderer);


	mCollisionSystem = std::shared_ptr<CollisionSystem>();

	mPhysicsSystem = std::shared_ptr<PhysicsSystem>();

	const auto threadManager = ThreadManager::Instance();

	mRenderSystemThreadID = threadManager->AddThread(&RenderSystem::Start, mRenderSystem);
	mCollisionSystemThreadID = threadManager->AddThread(&CollisionSystem::Start, mCollisionSystem);
	mPhysicsSystemThreadID = threadManager->AddThread(&PhysicsSystem::Start, mPhysicsSystem);

}

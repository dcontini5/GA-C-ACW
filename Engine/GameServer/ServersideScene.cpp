#include "ServersideScene.h"



#include "CollisionSystem.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"

void ServersideScene::Start(){


	std::shared_ptr<System> physicsSystem = std::make_shared<PhysicsSystem>();
	std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>();

	AddSystem(physicsSystem);
	AddSystem(collisionSystem);


	auto planeObj = std::make_shared<GameObject>();
	
	planeObj->SetPos({ 0, 0, 0 });
	planeObj->setRot({ 0, 0, 0 });
	planeObj->setScale({ 1, 1, 1 });
	
	{

		auto cc = std::make_shared<InfinitePlaneCollisionComponent>(planeObj);
		cc->SetNormal({0, 1, 0});
		
		auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);
		
		planeObj->AddComponent(comp);
		
	}

	mGameObjectList.push_back(planeObj);
	
	auto sphereObj = std::make_shared<GameObject>();
	
	sphereObj->SetPos({ 0, 5, -15 });
	sphereObj->setRot({ 0, 0, 0 });
	sphereObj->setScale({ 1, 1, 1 });

	{

		auto cc = std::make_shared<SphereCollisionComponent>(sphereObj);
		cc->SetRadius(1.0);

		auto collComp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

		auto pc = std::make_shared<PhysicsComponent>(sphereObj);
		pc->SetStatic(false);
		pc->SetDrag(0.9f);
		pc->SetMass(1.f);
		pc->SetVelocity({ 0.f, 0.f, 0.f });
		
		sphereObj->AddComponent(collComp);

	}


	mGameObjectList.push_back(sphereObj);

	Scene::Start();

	
}

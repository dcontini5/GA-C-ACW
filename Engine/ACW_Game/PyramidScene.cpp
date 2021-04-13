#include "PyramidScene.h"
#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Game.h"
#include "InfinitePlaneCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "ThreadManager.h"

void PyramidScene::Start(){

	auto renderer = Game::Instance()->GetWindow()->GetRenderer();
	
	std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
	std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(renderer);

	std::shared_ptr<System> physicsSystem = std::make_shared<PhysicsSystem>();

	std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>();
	
	
	AddSystem(collisionSystem);
	AddSystem(renderSystem);
	AddSystem(physicsSystem);

	auto planeObj = std::make_shared<GameObject>();


	
	planeObj->SetPos({ 0.f, -3.f, 0.f });
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

	int noOfBalls = 1;
	
	for (auto i = 0; i < noOfBalls; i++) {
		
		auto sphereObj = std::make_shared<GameObject>();
	
		sphereObj->SetPos({ -0/* * 0.5f + i * 3*/, 10.f + i * i , -5 });
		sphereObj->setRot({ 0, 0, 0 });
		sphereObj->setScale({ 1, 1, 1 });

		{
			
			auto rc = std::make_shared<RenderComponent>(sphereObj);
			auto mesh = ResourceManager::Instance()->GetMesh("Sphere");

			rc->SetMesh(mesh);
			rc->StartDrawing();

			auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(rc);

			sphereObj->AddComponent(comp);

			auto pc = std::make_shared<PhysicsComponent>(sphereObj);
			pc->SetDrag(0.60f);
					
			comp = std::reinterpret_pointer_cast<GameObjectComponent>(pc);

			sphereObj->AddComponent(comp);

			auto cc = std::make_shared<SphereCollisionComponent>(sphereObj);

			cc->SetRadius(1.f);

			comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);
			
			sphereObj->AddComponent(comp);
		}

		
		mGameObjectList.push_back(sphereObj);
		
	}
	
	
	{

		auto sphereObj = std::make_shared<GameObject>();

		sphereObj->SetPos({ -0.2, 2.f , -5.1 });
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
			//pc->SetStatic(true);
			
			comp = std::reinterpret_pointer_cast<GameObjectComponent>(pc);

			sphereObj->AddComponent(comp);

			auto cc = std::make_shared<SphereCollisionComponent>(sphereObj);

			cc->SetRadius(1.f);

			comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

			sphereObj->AddComponent(comp);
		}


		mGameObjectList.push_back(sphereObj);

		
	}


	{

		auto sphereObj = std::make_shared<GameObject>();

		sphereObj->SetPos({ 0.2, 5.f , -4.9 });
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
			//pc->SetStatic(true);

			comp = std::reinterpret_pointer_cast<GameObjectComponent>(pc);

			sphereObj->AddComponent(comp);

			auto cc = std::make_shared<SphereCollisionComponent>(sphereObj);

			cc->SetRadius(1.f);

			comp = std::reinterpret_pointer_cast<GameObjectComponent>(cc);

			sphereObj->AddComponent(comp);
		}


		mGameObjectList.push_back(sphereObj);


	}


	
	
	Scene::Start();
	
}

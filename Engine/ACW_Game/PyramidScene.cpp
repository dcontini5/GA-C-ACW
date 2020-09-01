#include "PyramidScene.h"
#include "RenderSystem.h"
#include "Game.h"
#include "ThreadManager.h"

void PyramidScene::Start(){

	auto renderer = Game::Instance()->GetWindow()->GetRenderer();
	
	std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
	std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(renderer);
	
	AddSystem(renderSystem);

	auto planeObj = std::make_shared<GameObject>();


	planeObj->SetPos({ 0, -3, 0 });
	planeObj->setRot({ 0, 0, 0 });
	planeObj->setScale({ 1, 1, 1 });
	
	{

		auto rc = std::make_shared<RenderComponent>(planeObj);
		auto mesh = ResourceManager::Instance()->GetMesh("Plane");

		rc->SetMesh(mesh);
		rc->StartDrawing();

		auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(rc);

		planeObj->AddComponent(comp);
		
	}
		
	mGameObjectList.push_back(planeObj);


	
	auto sphereObj = std::make_shared<GameObject>();
	
	sphereObj->SetPos({ 0, 0, -15 });
	sphereObj->setRot({ 0, 0, 0 });
	sphereObj->setScale({ 1, 1, 1 });

	{
		
		auto rc = std::make_shared<RenderComponent>(sphereObj);
		auto mesh = ResourceManager::Instance()->GetMesh("Sphere");

		rc->SetMesh(mesh);
		rc->StartDrawing();

		auto comp = std::reinterpret_pointer_cast<GameObjectComponent>(rc);

		sphereObj->AddComponent(comp);
		
	}

	
	mGameObjectList.push_back(sphereObj);



	
	
	Scene::Start();
	
}

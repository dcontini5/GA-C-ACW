#include "PyramidScene.h"
#include "RenderSystem.h"

void PyramidScene::Start(std::shared_ptr<Renderer>& pRenderer){

	std::shared_ptr<System> renderSystem = std::make_shared<RenderSystem>();
	std::dynamic_pointer_cast<RenderSystem>(renderSystem)->SetRenderer(pRenderer);
	
	AddSystem(renderSystem);

	auto gameobj = std::make_shared<GameObject>();

	gameobj->setRot({ 0, 0, 0 });
	gameobj->SetPos({ 0, 0, 0 });
	gameobj->setScale({ 1, 1, 1 });

	
	{
		
		auto rc = std::make_shared<RenderComponent>(gameobj);
		
	}
	
	//gameobj->AddComponent()
	
	mGameObjectList.push_back(gameobj);

	
	Scene::Start();
	
}

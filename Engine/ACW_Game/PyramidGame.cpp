#include "PyramidGame.h"
#include "ResourceManager.h"
#include "PyramidScene.h"

void PyramidGame::Initialize(std::shared_ptr<Window>& pWindow){

	Game::Initialize(pWindow);
	
	auto renderer = mWindow->GetRenderer();
	
	ResourceManager::Instance()->LoadMesh(PLANE, renderer);
	ResourceManager::Instance()->LoadMesh(SPHERE, renderer);

	
	mScene = std::make_shared<PyramidScene>();

	mScene->Start();

	
}

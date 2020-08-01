#include "PyramidGame.h"
#include "ResourceManager.h"
#include "PyramidScene.h"

void PyramidGame::Initialize(){

	auto renderer = mWindow->GetRenderer();
	
	ResourceManager::Instance()->LoadMesh(PLANE, renderer);

	mScene = std::make_shared<PyramidScene>();

	mScene->Start();

	
}

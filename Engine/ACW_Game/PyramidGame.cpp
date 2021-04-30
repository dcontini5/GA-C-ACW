#include "PyramidGame.h"
#include "ResourceManager.h"
#include "PyramidScene.h"
#include "ClientUI.h"

void PyramidGame::Initialize(std::shared_ptr<Window>& pWindow){

	Game::Initialize(pWindow);


	
	auto renderer = mWindow->GetRenderer();

	std::unique_ptr<UI> myUI = std::make_unique<ClientUI>();
	
	renderer->SetUI(myUI);
	renderer->InitUi();
	
	ResourceManager::Instance()->LoadMesh(PLANE, renderer);
	ResourceManager::Instance()->LoadMesh(SPHERE, renderer);

	
	mScene = std::make_shared<PyramidScene>();

	mScene->Start();

	
}

#include "RenderSystem.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ThreadManager.h"
#include "Game.h"

void RenderSystem::Process(){

	mRenderer->ClearScreen();

	
	
	for(const auto& object: mGameObjects){

		std::shared_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
		
		const auto renderComponent = std::reinterpret_pointer_cast<RenderComponent>(object->GetComponent(ComponentTypes::RENDER));

		if (!renderComponent->IsDrawable()) continue;
		
		auto mesh = renderComponent->GetMesh();
		const auto pos = object->GetOldPos();
		const auto scale = object->GetScale();
	
		mRenderer->Render(mesh, pos, scale);
	}

	mRenderer->Present();
	
}

void RenderSystem::Start(){

	
	while (Game::Instance()->GetQuitFlag()){

		Process();
		
	}

	
}



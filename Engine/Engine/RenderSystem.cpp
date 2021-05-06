#include "RenderSystem.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ThreadManager.h"
#include "Game.h"
#include "CurrentSystemFrequencyMessage.h"

void RenderSystem::Process(){
	
	{

		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->GetConditionVariable().wait(lk, [] {
			return !ThreadManager::Instance()->IsRendererPaused();
		});

	}

	
	std::chrono::duration<double> lag = std::chrono::high_resolution_clock::now() - mLastTime;

	while (lag < mTimeStep){
		lag = std::chrono::high_resolution_clock::now() - mLastTime;
	}

	//avgFps code taken from https://stackoverflow.com/questions/4687430/c-calculating-moving-fps
	static auto avgFps = 1.f;
	const auto alpha = 0.8f;
	avgFps = alpha * avgFps + (1.f - alpha) * 1 / lag.count();
	//
	
	std::shared_ptr<Message> msg = std::make_shared<CurrentSystemFrequencyMessage>(SystemTypes::RENDER, avgFps);
	Game::Instance()->BroadcastMessage(msg);
	
	mLastTime = std::chrono::high_resolution_clock::now();
	
	mRenderer->ClearScreen();
	mRenderer->UpdateViewMatrix();
	
	for(const auto& object: mGameObjects){

		std::shared_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
		
		const auto renderComponent = std::reinterpret_pointer_cast<RenderComponent>(object->GetComponent(ComponentTypes::RENDER));

		if (!renderComponent->IsDrawable()) continue;
		
		auto mesh = renderComponent->GetMesh();
		const auto pos = object->GetPos();
		const auto scale = object->GetScale();
	
		mRenderer->Render(mesh, pos, scale);
	}

	mRenderer->RenderUI();
	
	mRenderer->Present();
	
	//mLastTime = std::chrono::high_resolution_clock::now();
	
}

void RenderSystem::Start(){

	
	while (Game::Instance()->GetQuitFlag()){

		Process();
		
	}

	
}



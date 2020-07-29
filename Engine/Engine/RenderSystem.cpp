#include "RenderSystem.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ThreadManager.h"

RenderSystem* RenderSystem::mInstance = nullptr;

void RenderSystem::Process(){

	for(const auto& object: mRenderableObjects){

		auto renderComponent = std::reinterpret_pointer_cast<RenderComponent>(object->GetComponent(Render));

		if (!renderComponent->IsDrawable()) continue;
		auto mesh = renderComponent->GetMesh();
		auto pos = object->GetPos();
		auto scale = object->GetScale();

		mRenderer->Render(mesh, pos, scale);
	}
}

void RenderSystem::AddObject(GameObjectPtr& pGameObject){

	mRenderableObjects.push_back(pGameObject);
	
}

void RenderSystem::RemoveObject(GameObjectPtr& pGameObject){

	auto it = mRenderableObjects.begin();
	for(const auto& object : mRenderableObjects){

		
		if(pGameObject == object){
			mRenderableObjects.erase(it);
			return;
		}
		++it;
	}
	
}

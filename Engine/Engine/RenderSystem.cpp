#include "RenderSystem.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ThreadManager.h"


void RenderSystem::Process(){

	for(const auto& object: mGameObjects){

		auto renderComponent = std::reinterpret_pointer_cast<RenderComponent>(object->GetComponent(ComponentTypes::RENDER));

		if (!renderComponent->IsDrawable()) continue;
		auto mesh = renderComponent->GetMesh();
		auto pos = object->GetPos();
		auto scale = object->GetScale();

		mRenderer->Render(mesh, pos, scale);
	}
}



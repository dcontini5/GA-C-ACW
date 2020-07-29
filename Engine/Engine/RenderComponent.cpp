#include "RenderComponent.h"
#include "RenderSystem.h"

RenderComponent::RenderComponent(GameObjectPtr& pParent) : GameObjectComponent(pParent, Render){

	RenderSystem::Instance()->AddObject(pParent);
	
} 

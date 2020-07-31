#include "RenderComponent.h"
#include "RenderSystem.h"

RenderComponent::RenderComponent(GameObjectPtr& pParent) : GameObjectComponent(pParent, ComponentTypes::RENDER){

	RenderSystem::Instance()->AddObject(pParent);
	
} 

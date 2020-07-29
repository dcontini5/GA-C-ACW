#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(GameObjectPtr& pParent, const ComponentTypes& pType)
: mParent(pParent), mType(pType){

	auto sft = shared_from_this();
	pParent->AddComponent(sft);
	
}

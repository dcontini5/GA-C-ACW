#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(GameObjectPtr& pParent, ComponentType& pType)
: mParent(pParent), mType(pType), Observer(){

	//auto sft = shared_from_this();
	//pParent->AddComponent(sft);

	//pParent->AddComponent(this);
	
}

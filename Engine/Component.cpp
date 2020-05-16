#include "Component.h"
Component::Component(std::shared_ptr<GameObject>& pParent, const ComponentType& pType)
: mParent(pParent), mType(pType){

	mParent->AddComponent(shared_from_this());
	
}

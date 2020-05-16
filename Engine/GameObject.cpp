#include "GameObject.h"


GameObject::GameObject(const glm::vec3& pPosition, const glm::vec3& pRotation, const glm::vec3& pScale):
	mPosition(pPosition), mRotation(pRotation), mScale(pScale) {
	
}

void GameObject::AddComponent(const std::shared_ptr<Component>& pComponent){

	
	if (mComponents.find(pComponent->GetComponentType()) != mComponents.end()) return;

	mComponents.insert(std::make_pair(pComponent->GetComponentType(), pComponent));
	
}

void GameObject::RemoveComponent(const ComponentType& pType){

	auto it = mComponents.find(pType);

	if(it != mComponents.end()){

		mComponents.erase(it);
		it->second->End();
		it->second.reset();
		
	}
	
}

std::shared_ptr<Component> GameObject::GetComponent(const ComponentType& pType){

	auto it = mComponents.find(pType);

	if (it != mComponents.end()) return it->second;

	return nullptr;

	
}

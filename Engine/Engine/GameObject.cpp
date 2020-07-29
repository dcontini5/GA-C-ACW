#include "GameObject.h"
#include "GameObjectComponent.h"

ComponentPtr GameObject::GetComponent(const ComponentTypes& pComponentName){

	ComponentMapIterator it = mComponents.find(pComponentName);

	if (it != mComponents.end()) {

		return it->second;

	}
	
	return nullptr;
}

void GameObject::AddComponent(ComponentPtr& pComponent){

	if(mComponents.find(pComponent->GetType()) != mComponents.end())
		return;

	mComponents[pComponent->GetType()] = pComponent;


	
}

void GameObject::RemoveComponent(const ComponentTypes& pType){

	ComponentMapIterator it = mComponents.find(pType);

	if(it != mComponents.end()){

		mComponents.erase(it);

		it->second; //todo Destroy component
		// todo delete it->second;
		
	}

	
}


void GameObject::RemoveComponent(ComponentPtr& pComponent){

	RemoveComponent(pComponent->GetType());
	
}

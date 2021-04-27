#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Game.h"
#include "AddedComponentMessage.h"
#include "RemovedComponentMessage.h"

static int IDs = 0;

GameObject::GameObject():mID(IDs++){}

ComponentPtr GameObject::GetComponent(const int& pComponentName){

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
	auto imThis = shared_from_this();
	std::shared_ptr<Message> msg = std::make_shared<AddedComponentMessage>(pComponent->GetType(), imThis);
	Game::Instance()->BroadcastMessage(msg);

	
}

void GameObject::AddComponent(GameObjectComponent* pComponent){


	
	if(mComponents.find(pComponent->GetType()) != mComponents.end())
		return;

	mComponents[pComponent->GetType()] = std::make_shared<GameObjectComponent>(*pComponent);
	auto imThis = shared_from_this();
	std::shared_ptr<Message> msg = std::make_shared<AddedComponentMessage>(pComponent->GetType(), imThis);
	Game::Instance()->BroadcastMessage(msg);
	
}

void GameObject::RemoveComponent(const int& pType){

	ComponentMapIterator it = mComponents.find(pType);

	if(it != mComponents.end()){

		mComponents.erase(it);

		auto imThis = shared_from_this();
		std::shared_ptr<Message> msg = std::make_shared<RemovedComponentMessage>(it->second->GetType(), imThis);
		Game::Instance()->BroadcastMessage(msg);
		//todo Destroy component
		// todo delete it->second;
		
	}

	
}


void GameObject::RemoveComponent(ComponentPtr& pComponent){

	RemoveComponent(pComponent->GetType());
	
}

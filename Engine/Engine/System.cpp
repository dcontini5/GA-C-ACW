#include "System.h"

void System::AddObject(GameObjectPtr& pGameObject) {

	mGameObjects.push_back(pGameObject);

}

void System::RemoveObject(GameObjectPtr& pGameObject) {

	auto it = mGameObjects.begin();
	for (const auto& object : mGameObjects) {


		++it;
		if (pGameObject == object) {
			mGameObjects.erase(it);
			return;
		}
	}

}

void System::RemoveObjectByID(const int& pID){


	auto it = mGameObjects.begin();
	for (const auto& object : mGameObjects) {

		++it;
		if (object->GetId() == pID) {
			mGameObjects.erase(it);
			return;
		}
	}
	
}

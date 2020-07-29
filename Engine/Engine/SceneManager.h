#pragma once
#include <vector>
#include "GameObject.h"

typedef std::vector<std::shared_ptr<GameObject>> GameObjects;


class SceneManager {

	//Private Structors
private:
	SceneManager() = default;

	//Public Structors
public:
	~SceneManager() = default;

	static SceneManager* Instance(){

		if (!mInstance){ mInstance = new SceneManager(); }

		return mInstance;
	}

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	GameObjects GetGameObjects() { return GameObjectList; }
	// Private Functions
private:

	//Data:
private:
	static SceneManager* mInstance;

	GameObjects GameObjectList;
	
};

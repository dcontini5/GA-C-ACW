#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameObjectComponent.h"


typedef std::vector<std::shared_ptr<GameObject>> GameObjects;

class System {

	//Structors
public:
	System() = default;
	System(const System&);
	System(System&&); //exchange members here;
	~System();

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	virtual void Process() = 0;
	virtual void Start() = 0;
	void AddObject(GameObjectPtr& pGameObject);
	void RemoveObject(GameObjectPtr& pGameObject);
	
	// Private Functions
private:

	//Operators
public:
	System& operator=(const System& pOther) = delete;

	System& operator=(const System&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:

	GameObjects mGameObjects;
	
};

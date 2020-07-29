#pragma once
#include "GameObject.h"
#include "GameObjectComponent.h"

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
	virtual void AddObject(GameObjectPtr& pGameObject) = 0;
	virtual void RemoveObject(GameObjectPtr& pGameObject) = 0;
	
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
private:

	
};

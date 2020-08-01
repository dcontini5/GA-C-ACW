#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Scene.h"
#include "SystemTypes.h"

class System {

	//Structors
public:
	System(SystemType& pType): mType(pType){}
	System(const System&);
	System(System&&); //exchange members here;
	~System() = default;

	//Accessors
public:

	SystemType GetType() const { return mType; }
	
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
	SystemType mType;
};

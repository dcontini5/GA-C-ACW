#pragma once
#include <memory>
//#include "GameObject.h"

class GameObject;

typedef std::shared_ptr<GameObject> GameObjectPtr;

enum ComponentTypes {

	Render,
	Collision,
	Physics,
	Network, //maybe
	
};


class GameObjectComponent : std::enable_shared_from_this<GameObjectComponent> {

	//Structors
public:
	GameObjectComponent(GameObjectPtr& pParent, const ComponentTypes& pType);
	GameObjectComponent(const GameObjectComponent&);
	GameObjectComponent(GameObjectComponent&&); //exchange members here;
	~GameObjectComponent() = default;

	//Accessors
public:
	GameObjectPtr GetParent() const{ return mParent; }
	ComponentTypes GetType() const { return mType; }
	//Mutators
public:

	// Public Functions
public:
	
	// Private Functions
private:

	//Operators
public:
	GameObjectComponent& operator=(const GameObjectComponent& pOther){ return *this = GameObjectComponent(pOther); }

	GameObjectComponent& operator=(const GameObjectComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	GameObjectPtr mParent;
	ComponentTypes mType;
	
};

#pragma once
#include <memory>
#include "ComponentTypes.h"
#include "Observer.h"
//#include "GameObject.h"

class GameObject;

typedef std::shared_ptr<GameObject> GameObjectPtr;



class GameObjectComponent : std::enable_shared_from_this<GameObjectComponent>, public Observer {

	//Structors
public:
	GameObjectComponent(GameObjectPtr& pParent, ComponentType& pType);
	GameObjectComponent(const GameObjectComponent&);
	GameObjectComponent(GameObjectComponent&&); //exchange members here;
	~GameObjectComponent() = default;

	//Accessors
public:
	GameObjectPtr GetParent() const{ return mParent; }
	ComponentType GetType() const { return mType; }
	//Mutators
public:

	// Public Functions
public:
	
	// Private Functions
private:

	//Operators
public:
	GameObjectComponent& operator=(const GameObjectComponent& pOther) = delete;

	GameObjectComponent& operator=(const GameObjectComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	GameObjectPtr mParent;
	ComponentType mType;
	
};

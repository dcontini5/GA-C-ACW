#pragma once
#include "GameObjectComponent.h"

typedef const int ColliderType;

struct ColliderTypes {

	static ColliderType SPHERE = 1;
	static ColliderType PLANE = 2;
	
};


class CollisionComponent : public GameObjectComponent {

	//Structors
public:
	CollisionComponent(GameObjectPtr& pParent, ColliderType& pCollider): GameObjectComponent(pParent, ComponentTypes::COLLISION), mCollider(pCollider){}
	CollisionComponent(const CollisionComponent&);
	CollisionComponent(CollisionComponent&&); //exchange members here;
	~CollisionComponent() = default;

	//Accessors
public:
	ColliderType GetColliderType() const { return mCollider; }
	
	//Mutators
public:

	// Public Functions
public:
	void OnMessage(std::shared_ptr<Message>& pMessage) override {}
	
	// Private Functions
private:

	//Operators
public:
	CollisionComponent& operator=(const CollisionComponent& pOther){ return *this = CollisionComponent(pOther); }

	CollisionComponent& operator=(const CollisionComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	ColliderType mCollider;
	
};

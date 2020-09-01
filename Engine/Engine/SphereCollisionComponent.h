#pragma once
#include "CollisionComponent.h"

class SphereCollisionComponent : public CollisionComponent {

	//Structors
public:
	SphereCollisionComponent(GameObjectPtr& pParent);
	SphereCollisionComponent(const SphereCollisionComponent&);
	SphereCollisionComponent(SphereCollisionComponent&&); //exchange members here;
	~SphereCollisionComponent() = default;

	//Accessors
public:
	float GetRadius() const { return mRadius; }
	
	//Mutators
public:

	void SetRadius(const float& pRadius) { mRadius = pRadius; }
	
	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	SphereCollisionComponent& operator=(const SphereCollisionComponent& pOther){ return *this = SphereCollisionComponent(pOther); }

	SphereCollisionComponent& operator=(const SphereCollisionComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	float mRadius = 0;
	
};

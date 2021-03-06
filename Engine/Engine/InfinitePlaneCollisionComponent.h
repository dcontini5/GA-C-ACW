﻿#pragma once
#include <glm.hpp>
#include "CollisionComponent.h"


class InfinitePlaneCollisionComponent : public  CollisionComponent {

	//Structors
public:
	InfinitePlaneCollisionComponent(GameObjectPtr& pParent): CollisionComponent(pParent, ColliderTypes::PLANE) {}
	InfinitePlaneCollisionComponent(const InfinitePlaneCollisionComponent&);
	InfinitePlaneCollisionComponent(InfinitePlaneCollisionComponent&&); //exchange members here;
	~InfinitePlaneCollisionComponent() = default;

	//Accessors
public:
	glm::vec3 GetNormal() const { return mNormal; }
	//Mutators
public:

	void SetNormal(const glm::vec3& pNormal) { mNormal = pNormal; }
	
	// Public Functions
public:

	
	// Private Functions
private:

	//Operators
public:
	InfinitePlaneCollisionComponent& operator=(const InfinitePlaneCollisionComponent& pOther){ return *this = InfinitePlaneCollisionComponent(pOther); }

	InfinitePlaneCollisionComponent& operator=(const InfinitePlaneCollisionComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	glm::vec3 mNormal;
};

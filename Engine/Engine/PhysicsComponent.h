#pragma once
#include "GameObjectComponent.h"
#include <glm.hpp>

class PhysicsComponent : public GameObjectComponent {

	//Structors
public:
	
	PhysicsComponent(GameObjectPtr& pParent);
	~PhysicsComponent();

private:
	
	PhysicsComponent(const PhysicsComponent&);
	PhysicsComponent(PhysicsComponent&&); //exchange members here;
	
	//Accessors
public:
	glm::vec3 GetVelocity() const { return mVelocity; }
	bool IsStatic() const { return mStatic; }
	float GetMass() const { return mMass; }
	float GetDrag() const { return  mDrag; }
	//Mutators
public:
	void SetVelocity(const glm::vec3& pVelocity) { mVelocity = pVelocity; }
	void SetStatic(const bool& pStatic) { mStatic = pStatic; }
	void SetMass(const float& pMass) { mMass = pMass; }
	void SetDrag(const float& pDrag) { mDrag = pDrag; }
	// Public Functions
public:

	void OnMessage(std::shared_ptr<Message>& pMessage) override {};
	
	// Private Functions
private:

	//Operators
public:
	
	PhysicsComponent& operator=(const PhysicsComponent& pOther){ return *this = PhysicsComponent(pOther); }
	PhysicsComponent& operator=(const PhysicsComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	glm::vec3 mVelocity;
	bool	  mStatic;
	float     mMass;
	float	  mDrag;

	
};

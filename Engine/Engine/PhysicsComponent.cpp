#include "PhysicsComponent.h"
#include "PhysicsSystem.h"

PhysicsComponent::PhysicsComponent(GameObjectPtr& pParent):GameObjectComponent(pParent, ComponentTypes::PHYSICS), mVelocity(0,0,0), mStatic(false), mMass(1.f), mDrag(0.5) {

	//PhysicsSystem::Instance()->AddObject(pParent);
	
}

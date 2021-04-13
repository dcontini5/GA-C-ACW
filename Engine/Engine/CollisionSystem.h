#pragma once
#include "System.h"
#include "PhysicsComponent.h"

class InfinitePlaneCollisionComponent;
class SphereCollisionComponent;

typedef std::shared_ptr<SphereCollisionComponent> SphereCollisionPtr;
typedef std::shared_ptr<InfinitePlaneCollisionComponent> PlaneCollisionPtr;
typedef std::shared_ptr<PhysicsComponent> PhysicsComponentPtr;

class CollisionSystem : public System {

	//Private Structors
private:


	//Public Structors
public:
	CollisionSystem() :System(SystemTypes::COLLISION) {};
	~CollisionSystem() = default;	
	//Accessors

	
	//Mutators
public:

	// Public Functions
public:
	
	void Process() override;
	void Start() override;
	
	// Private Functions
private:

	void CheckCollision(ComponentPtr& pCollider, ComponentPtr& pCollidee);
	void CheckSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee);
	void CheckPlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee);

	void CollisionResponseStatic(PhysicsComponentPtr& pCollider, const float& pDistance, const glm::vec3& pNormal);
	void CollisionResponseDynamic(PhysicsComponentPtr& pCollider, PhysicsComponentPtr& pCollidee, const float& pDistance, const glm::vec3& pNormal);

	//Data:
private:

		
};



#pragma once
#include "System.h"

class InfinitePlaneCollisionComponent;
class SphereCollisionComponent;

typedef std::shared_ptr<SphereCollisionComponent> SphereCollisionPtr;
typedef std::shared_ptr<InfinitePlaneCollisionComponent> PlaneCollisionPtr;

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

	bool CheckCollision(ComponentPtr& pCollider, ComponentPtr& pCollidee);
	bool CheckSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee);
	bool CheckPlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee);
	void CollisionResponse(ComponentPtr& pCollider, ComponentPtr& pCollidee);
	void ResponseSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee);
	void ResponsePlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee);

	//Data:
private:

		
};

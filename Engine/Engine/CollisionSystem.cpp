#include "CollisionSystem.h"
#include "Message.h"
#include "SphereCollisionComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "PhysicsComponent.h"


void CollisionSystem::Process(){

	for(size_t i = 0; i <= mGameObjects.size(); i++){

		auto collider = mGameObjects[i]->GetComponent(ComponentTypes::COLLISION);
		
		for(auto j = i + 1 ; j < mGameObjects.size(); j ++){

			
			auto collidee = mGameObjects[j]->GetComponent(ComponentTypes::COLLISION);
			
			if(CheckCollision(collider, collidee)){

				//CollisionResponse()
				
				auto msg = std::make_shared<Message>(MessageTypes::COLLISION);
				collider->GetParent()->BroadcastMessage(msg);
				collidee->GetParent()->BroadcastMessage(msg);
				
			}

		}

	}

}


void CollisionSystem::Start(){}



bool CollisionSystem::CheckCollision(ComponentPtr& pCollider, ComponentPtr& pCollidee){

	const std::shared_ptr<CollisionComponent> collider = std::dynamic_pointer_cast<CollisionComponent>(pCollider);
	const std::shared_ptr<CollisionComponent> collidee = std::dynamic_pointer_cast<CollisionComponent>(pCollidee);


	
	if (collider->GetColliderType() == collidee->GetColliderType()) {
		
		auto sphereCollider = std::dynamic_pointer_cast<SphereCollisionComponent>(collider);
		auto sphereCollidee = std::dynamic_pointer_cast<SphereCollisionComponent>(collidee);
		
		return (CheckSphereSphere(sphereCollider, sphereCollidee));
		
	}

	auto planeCollider = std::dynamic_pointer_cast<InfinitePlaneCollisionComponent>(collider);
	auto sphereCollidee = std::dynamic_pointer_cast<SphereCollisionComponent>(collidee);
	
	return CheckPlaneSphere(planeCollider, sphereCollidee);
	
}

bool CollisionSystem::CheckSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee){

	const auto dist =abs( pCollider->GetParent()->GetPos() - pCollidee->GetParent()->GetPos() );

	const auto distLenght = glm::dot(dist, dist);

	const auto radSum = pCollider->GetRadius() + pCollidee->GetRadius();
	
	return (distLenght <= radSum) ;
		
}



bool CollisionSystem::CheckPlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee){

	const auto dist = abs(pPlaneCollider->GetParent()->GetPos() - pSphereCollidee->GetParent()->GetPos());

	const auto distLenght = glm::dot( dist,  pPlaneCollider->GetNormal());

	const auto r = pSphereCollidee->GetRadius();
	
	return (distLenght <= r * r);
	
	
}



void CollisionSystem::ResponsePlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee){

	const auto sphereSparent = pSphereCollidee->GetParent();

	const auto diff = (glm::vec3(pSphereCollidee->GetRadius()) - sphereSparent->GetPos()) * pPlaneCollider->GetNormal();
	
	sphereSparent->SetPos( sphereSparent->GetPos() + diff );

	const auto collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pSphereCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

	const auto reflectedVel = glm::reflect(collideePhysComp->GetVelocity(), pPlaneCollider->GetNormal());
	
	collideePhysComp->SetVelocity( glm::vec3(reflectedVel.x * 0.9, reflectedVel.y * 0.9, reflectedVel.z * 0.9) );
	
}

void CollisionSystem::ResponseSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee){

	const auto colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollider->GetParent()->GetComponent(ComponentTypes::PHYSICS));
	const auto collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

	if (colliderPhysComp->IsStatic()) {
		
		const auto collNormal = glm::normalize(pCollidee->GetParent()->GetPos() - pCollider->GetParent()->GetPos());

		const auto diff = (glm::vec3(pCollidee->GetRadius()) - pCollidee->GetParent()->GetPos()) * collNormal;

		pCollidee->GetParent()->SetPos(pCollidee->GetParent()->GetPos() + diff);

		const auto collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

		const auto reflectedVel = glm::reflect(collideePhysComp->GetVelocity(), collNormal);

		collideePhysComp->SetVelocity(glm::vec3(reflectedVel.x * 0.9, reflectedVel.y * 0.9, reflectedVel.z * 0.9));
		
	}
	else if(collideePhysComp->IsStatic()){

		const auto collNormal = glm::normalize(pCollider->GetParent()->GetPos() - pCollidee->GetParent()->GetPos());

		const auto diff = (glm::vec3(pCollider->GetRadius()) - pCollider->GetParent()->GetPos()) * collNormal;

		pCollider->GetParent()->SetPos(pCollider->GetParent()->GetPos() + diff);

		const auto colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollider->GetParent()->GetComponent(ComponentTypes::PHYSICS));

		const auto reflectedVel = glm::reflect(colliderPhysComp->GetVelocity(), collNormal);

		colliderPhysComp->SetVelocity(glm::vec3(reflectedVel.x * 0.9, reflectedVel.y * 0.9, reflectedVel.z * 0.9));

	}	else{


		const auto colliderNormal = glm::normalize(pCollider->GetParent()->GetPos() - pCollidee->GetParent()->GetPos());
		
		const auto diff = (glm::vec3(pCollider->GetRadius()) - pCollider->GetParent()->GetPos()) * colliderNormal;

		pCollider->GetParent()->SetPos(pCollider->GetParent()->GetPos() + diff);

		const auto colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollider->GetParent()->GetComponent(ComponentTypes::PHYSICS));
		const auto collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

		const auto reflectedVelCollider = glm::reflect(colliderPhysComp->GetVelocity(), colliderNormal);
		const auto reflectedVelCollidee = glm::reflect(collideePhysComp->GetVelocity(), -colliderNormal);
	
		colliderPhysComp->SetVelocity(glm::vec3(reflectedVelCollider.x * 0.9, reflectedVelCollider.y * 0.9, reflectedVelCollider.z * 0.9));
		collideePhysComp->SetVelocity(glm::vec3(reflectedVelCollidee.x * 0.9, reflectedVelCollidee.y * 0.9, reflectedVelCollidee.z * 0.9));
		
	}
	
}

void CollisionSystem::CollisionResponse(ComponentPtr& pCollider, ComponentPtr& pCollidee){

	const std::shared_ptr<CollisionComponent> collider = std::dynamic_pointer_cast<CollisionComponent>(pCollider);
	const std::shared_ptr<CollisionComponent> collidee = std::dynamic_pointer_cast<CollisionComponent>(pCollidee);



	if (collider->GetColliderType() == collidee->GetColliderType()) {

		auto sphereCollider = std::dynamic_pointer_cast<SphereCollisionComponent>(collider);
		auto sphereCollidee = std::dynamic_pointer_cast<SphereCollisionComponent>(collidee);

		
		
		//if(!colliderPhysComp->IsStatic()) ResponseSphereSphere(sphereCollider, sphereCollidee);
		//if(!collideePhysComp->IsStatic()) ResponseSphereSphere(sphereCollidee, sphereCollider);

	}

	auto planeCollider = std::dynamic_pointer_cast<InfinitePlaneCollisionComponent>(collider);
	auto sphereCollidee = std::dynamic_pointer_cast<SphereCollisionComponent>(collidee);

	ResponsePlaneSphere(planeCollider, sphereCollidee);
	
}

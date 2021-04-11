#include "CollisionSystem.h"

#include "Game.h"
#include "Message.h"
#include "SphereCollisionComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "PhysicsComponent.h"
#include "ThreadManager.h"


void CollisionSystem::Process(){

		
	{
		//auto mutex = ThreadManager::Instance()->GetMutex();
		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->GetConditionVariable().wait(lk, []{
			return ThreadManager::Instance()->IsPhysicsDone();
		});
		
	}
	
	for(auto i = 0; i <= mGameObjects.size() - 1; i++){

		auto collider = mGameObjects[i]->GetComponent(ComponentTypes::COLLISION);
		
		for(auto j = i + 1 ; j < mGameObjects.size(); j ++){

			
			auto collidee = mGameObjects[j]->GetComponent(ComponentTypes::COLLISION);
			
			if(CheckCollision(collider, collidee)){

				//CollisionResponse()
				CollisionResponse(collider, collidee);
				
				auto msg = std::make_shared<Message>(MessageTypes::COLLISION);
				collider->GetParent()->BroadcastMessage(msg);
				collidee->GetParent()->BroadcastMessage(msg);
				
			}

		}

	}

	ThreadManager::Instance()->SetPhysicsDone(false);
	ThreadManager::Instance()->GetConditionVariable().notify_one();
	
}


void CollisionSystem::Start(){

	while(Game::Instance()->GetQuitFlag()){

		Process();
		
	}
	
}



bool CollisionSystem::CheckCollision(ComponentPtr& pCollider, ComponentPtr& pCollidee){

	std::shared_ptr<CollisionComponent> collider = std::dynamic_pointer_cast<CollisionComponent>(pCollider);
	std::shared_ptr<CollisionComponent> collidee = std::dynamic_pointer_cast<CollisionComponent>(pCollidee);


	
	if (collider->GetColliderType() == collidee->GetColliderType()) {
		
		auto sphereCollider = std::static_pointer_cast<SphereCollisionComponent>(collider);
		auto sphereCollidee = std::static_pointer_cast<SphereCollisionComponent>(collidee);
		
		return (CheckSphereSphere(sphereCollider, sphereCollidee));
		
	}

	std::shared_ptr<InfinitePlaneCollisionComponent> planeCollider = nullptr;
	std::shared_ptr<SphereCollisionComponent> sphereCollidee = nullptr;
	
	if(collider->GetColliderType() == ColliderTypes::PLANE){
		planeCollider = std::static_pointer_cast<InfinitePlaneCollisionComponent>(collider);
		sphereCollidee = std::static_pointer_cast<SphereCollisionComponent>(collidee);
		
	}else{

		planeCollider = std::static_pointer_cast<InfinitePlaneCollisionComponent>(collidee);
		sphereCollidee = std::static_pointer_cast<SphereCollisionComponent>(collider);
				
	}
		
	return CheckPlaneSphere(planeCollider, sphereCollidee);
}

bool CollisionSystem::CheckSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee){

	const auto dist = abs( pCollider->GetParent()->GetPos() - pCollidee->GetParent()->GetPos() );

	const auto distLenght = glm::dot(dist, dist);

	const auto radSum = pCollider->GetRadius() + pCollidee->GetRadius();
	
	return (distLenght < radSum * radSum) ;
		
}



bool CollisionSystem::CheckPlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee){

	const auto dist = abs(pPlaneCollider->GetParent()->GetPos() - pSphereCollidee->GetParent()->GetPos());

	const auto distLenght = glm::dot( dist,  pPlaneCollider->GetNormal());

	const auto r = pSphereCollidee->GetRadius();
	
	return (distLenght <= r * r);
	
	
}



void CollisionSystem::ResponsePlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee){

	const auto sphereParent = pSphereCollidee->GetParent();

	const auto diff = glm::abs((sphereParent->GetPos() - pSphereCollidee->GetRadius()) * pPlaneCollider->GetNormal() - pPlaneCollider->GetParent()->GetPos());
		
	sphereParent->SetPos(sphereParent->GetPos() + diff * 1.1f);

	const auto collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pSphereCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

	const auto reflectedVel = glm::reflect(collideePhysComp->GetVelocity(), pPlaneCollider->GetNormal()) * 0.9f;
	
	collideePhysComp->SetVelocity(reflectedVel);
	
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

	}else{
		
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

		ResponseSphereSphere(sphereCollider, sphereCollidee);
		return;
		//if(!colliderPhysComp->IsStatic()) ResponseSphereSphere(sphereCollider, sphereCollidee);
		//if(!collideePhysComp->IsStatic()) ResponseSphereSphere(sphereCollidee, sphereCollider);

	}

	auto planeCollider = std::static_pointer_cast<InfinitePlaneCollisionComponent>(collider);
	auto sphereCollidee = std::static_pointer_cast<SphereCollisionComponent>(collidee);

	ResponsePlaneSphere(planeCollider, sphereCollidee);
	
}

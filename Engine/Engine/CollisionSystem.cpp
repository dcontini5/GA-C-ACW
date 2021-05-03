#include "CollisionSystem.h"

#include "Game.h"
#include "Message.h"
#include "SphereCollisionComponent.h"
#include "InfinitePlaneCollisionComponent.h"
#include "ThreadManager.h"


void CollisionSystem::Process(){

		
	{
		
		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->GetConditionVariable().wait(lk, []{
			return ThreadManager::Instance()->IsPhysicsDone();
		});
		
	}
	
	for(auto i = 0; i <= mGameObjects.size() - 1; i++){

		auto collider = mGameObjects[i]->GetComponent(ComponentTypes::COLLISION);
		
		for(auto j = i + 1 ; j < mGameObjects.size(); j ++){

			
			auto collidee = mGameObjects[j]->GetComponent(ComponentTypes::COLLISION);

			CheckCollision(collider, collidee);


		}

	}
	
	{
		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->SetPhysicsDone(false);
		ThreadManager::Instance()->GetConditionVariable().notify_one();
	}
}


void CollisionSystem::Start(){

	while(Game::Instance()->GetQuitFlag()){

		Process();
		
	}
	
}



void CollisionSystem::CheckCollision(ComponentPtr& pCollider, ComponentPtr& pCollidee){

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
		
	CheckPlaneSphere(planeCollider, sphereCollidee);
}

void CollisionSystem::CheckSphereSphere(SphereCollisionPtr& pCollider, SphereCollisionPtr& pCollidee){

	const auto dist = pCollider->GetParent()->GetNewPos() - pCollidee->GetParent()->GetNewPos();

	const auto distLenght = glm::dot(dist, dist);

	const auto radSum = pCollider->GetRadius() + pCollidee->GetRadius();

	if(distLenght < radSum * radSum){

		auto msg = std::make_shared<Message>(MessageTypes::COLLISION);
		pCollider->GetParent()->OnMessage(msg);
		pCollidee->GetParent()->OnMessage(msg);
		
		PhysicsComponentPtr colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollider->GetParent()->GetComponent(ComponentTypes::PHYSICS));
		PhysicsComponentPtr collideePhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));

		const auto distLenghtSquared = radSum - sqrt( distLenght);
		
		if (colliderPhysComp->IsStatic()) {
			CollisionResponseStatic(collideePhysComp, distLenghtSquared, glm::normalize(-dist));
			return;
		}
		if (collideePhysComp->IsStatic()) {
			CollisionResponseStatic(colliderPhysComp, distLenghtSquared, glm::normalize(dist));
			return;
		}

		CollisionResponseDynamic(colliderPhysComp, collideePhysComp, distLenghtSquared, glm::normalize(dist));

		
	}

}


void CollisionSystem::CheckPlaneSphere(PlaneCollisionPtr& pPlaneCollider, SphereCollisionPtr& pSphereCollidee){

	const auto dist = abs(pPlaneCollider->GetParent()->GetNewPos() - pSphereCollidee->GetParent()->GetNewPos());

	const auto distLenght = glm::dot( dist,  pPlaneCollider->GetNormal());

	const auto r = pSphereCollidee->GetRadius();
	
	if(distLenght <= r){

		const auto radiusMinusDist = r - distLenght;
		PhysicsComponentPtr colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pSphereCollidee->GetParent()->GetComponent(ComponentTypes::PHYSICS));
		CollisionResponseStatic(colliderPhysComp, radiusMinusDist, pPlaneCollider->GetNormal());

		auto msg = std::make_shared<Message>(MessageTypes::COLLISION);
		pPlaneCollider->GetParent()->OnMessage(msg);
		pSphereCollidee->GetParent()->OnMessage(msg);
		
	}
	
	
}

void CollisionSystem::CollisionResponseStatic(PhysicsComponentPtr& pCollider, const float& pDistance, const glm::vec3& pNormal){
	
	const auto diff = (pNormal * pDistance) * 1.000001f;

	pCollider->GetParent()->SetNewPos(pCollider->GetParent()->GetNewPos() + diff);

	const auto colliderPhysComp = std::dynamic_pointer_cast<PhysicsComponent>(pCollider->GetParent()->GetComponent(ComponentTypes::PHYSICS));

	const auto reflectedVel = glm::reflect(colliderPhysComp->GetVelocity(), pNormal);

	colliderPhysComp->SetVelocity(reflectedVel * 0.8f);
	
}

void CollisionSystem::CollisionResponseDynamic(PhysicsComponentPtr& pCollider, PhysicsComponentPtr& pCollidee, const float& pDistance, const glm::vec3& pNormal){

	const auto diff = (pNormal * pDistance) * 0.5000001f;
	
	pCollider->GetParent()->SetNewPos(pCollider->GetParent()->GetNewPos() + diff);
	pCollidee->GetParent()->SetNewPos(pCollidee->GetParent()->GetNewPos() - diff);
	
	const auto reflectedVelCollider = glm::reflect(pCollider->GetVelocity(), pNormal);
	const auto reflectedVelCollidee = glm::reflect(pCollidee->GetVelocity(), -pNormal);

	pCollider->SetVelocity(reflectedVelCollider * 0.8f);
	pCollidee->SetVelocity(reflectedVelCollidee * 0.8f);
	
}

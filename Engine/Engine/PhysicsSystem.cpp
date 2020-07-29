#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

PhysicsSystem* PhysicsSystem::mInstance = nullptr;

void PhysicsSystem::Process(){

	const auto now = std::chrono::steady_clock::now();
	const auto dt = std::chrono::duration<float>(now - mLastTime).count();
	mLastTime = now;

	for(auto& obj : mGameObjects){
				
		
		const auto physComp = std::reinterpret_pointer_cast<PhysicsComponent>(obj->GetComponent(Physics));

		if (physComp->IsStatic()) continue;
		
		const auto pos = obj->GetPos();

		const auto newVel = physComp->GetVelocity() * physComp->GetDrag();

		physComp->SetVelocity(newVel);
		
		const auto newPos =  pos + (newVel + mGravity) * dt;

		obj->SetPos(newPos);
		
	}
	
	
}

void PhysicsSystem::Start(){

	mLastTime = std::chrono::steady_clock::now();

	
}

#include "PhysicsSystem.h"

#include "Game.h"
#include "PhysicsComponent.h"
#include "ThreadManager.h"

#define DT_MULT 1.f


void PhysicsSystem::Process(){
	
	{
		
		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->GetConditionVariable().wait(lk, []{
			return !ThreadManager::Instance()->IsPhysicsDone();
		});
	
	}

	{
				
		for (auto& obj : mGameObjects) {
			std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
			obj->SetPos(obj->GetNewPos());
		}
		
	}
	
	std::chrono::duration<double> lag = std::chrono::high_resolution_clock::now() - mLastTime;
	
	while (lag < mTimeStep) {
		lag = std::chrono::high_resolution_clock::now() - mLastTime;
	}

	
	const auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> dt = now - mLastTime;
	mLastTime = now;
		
	for(auto& obj : mGameObjects){
				
		
		const auto physComp = std::reinterpret_pointer_cast<PhysicsComponent>(obj->GetComponent(ComponentTypes::PHYSICS));

		if (physComp->IsStatic()) continue;
		
		const auto pos = obj->GetNewPos();

		const auto newVel = physComp->GetVelocity() + mGravity * physComp->GetMass() * 0.1f;

		physComp->SetVelocity(newVel);
		
		const auto newPos =  pos + (newVel) * (dt.count() * DT_MULT);

		obj->SetNewPos(newPos);
		
	}
	
	{
		std::unique_lock<std::mutex> lk(ThreadManager::Instance()->GetMutex());
		ThreadManager::Instance()->SetPhysicsDone(true);
		ThreadManager::Instance()->GetConditionVariable().notify_one();
	}
	
	//mLastTime = std::chrono::high_resolution_clock::now();
	
}

void PhysicsSystem::Start(){

	mLastTime = std::chrono::steady_clock::now();

	while (Game::Instance()->GetQuitFlag()){

		Process();
		
	}

	
}

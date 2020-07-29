#pragma once
#include "System.h"
#include "chrono"

class PhysicsSystem : public System {

	//Private Structors
private:
	PhysicsSystem() = default;

	//Public Structors
public:
	~PhysicsSystem() = default;

	static PhysicsSystem* Instance(){

		if (!mInstance){ mInstance = new PhysicsSystem(); }

		return mInstance;
	}

	
	//Accessors

	//Mutators
public:

	// Public Functions
public:
	void Process() override;
	void Start() override;
	// Private Functions
private:

	//Data:
private:
	static PhysicsSystem* mInstance;

	const glm::vec3 mGravity = glm::vec3(0.f, 9.8f, 0.f);
	std::chrono::time_point<std::chrono::steady_clock> mLastTime;
	
};

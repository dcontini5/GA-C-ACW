#pragma once
#include "System.h"
#include "chrono"

class PhysicsSystem : public System {

	//Private Structors
private:

	//Public Structors
public:
	~PhysicsSystem() = default;
	PhysicsSystem() = default;

	
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

	const glm::vec3 mGravity = glm::vec3(0.f, 9.8f, 0.f);
	std::chrono::time_point<std::chrono::steady_clock> mLastTime;
	
};

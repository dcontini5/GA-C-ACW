#pragma once

class CollisionSystem {

	//Private Structors
private:
	CollisionSystem() = default;

	//Public Structors
public:
	~CollisionSystem() = default;

	static CollisionSystem* Instance(){

		if (!mInstance){ mInstance = new CollisionSystem(); }

		return mInstance;
	}

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Data:
private:
	static CollisionSystem* mInstance;


	
};

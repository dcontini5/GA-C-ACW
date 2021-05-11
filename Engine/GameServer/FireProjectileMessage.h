#pragma once
#include "Message.h"
#include "PyramidMessageTypes.h"

class FireProjectileMessage: public Message{

	//Structors
public:
	FireProjectileMessage(const uint8_t& pProjectileType) : Message(PyramidMessageTypes::FIRE_PROJECTILE), mProjectileType(pProjectileType) {}
	FireProjectileMessage(const FireProjectileMessage&);
	FireProjectileMessage(FireProjectileMessage&&); //exchange members here;
	~FireProjectileMessage() = default;

	//Accessors
public:
	uint8_t GetProjectileType()const { return mProjectileType; }
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	FireProjectileMessage& operator=(const FireProjectileMessage& pOther) = delete;

	FireProjectileMessage& operator=(const FireProjectileMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	uint8_t mProjectileType;
};

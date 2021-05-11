#pragma once
#include <vec3.hpp>

#include "Message.h"

class SpawnObjectMessage : public Message{

	//Structors
public:
	SpawnObjectMessage(const glm::vec3& pPos, const glm::vec3& pScale):Message(MessageTypes::SPAWN_OBJECT), mPosition(pPos), mScale(pScale) {}
	SpawnObjectMessage(const SpawnObjectMessage&);
	SpawnObjectMessage(SpawnObjectMessage&&); //exchange members here;
	~SpawnObjectMessage() = default;

	//Accessors
public:
	glm::vec3 GetPos() const { return mPosition; }
	glm::vec3 GetScale() const { return mScale; }
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	SpawnObjectMessage& operator=(const SpawnObjectMessage& pOther) = delete;

	SpawnObjectMessage& operator=(const SpawnObjectMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
};

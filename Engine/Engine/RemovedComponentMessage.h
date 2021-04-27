#pragma once
#include "ComponentTypes.h"
#include "Message.h"

class RemovedComponentMessage : public Message{

	//Structors
public:
	RemovedComponentMessage(ComponentType& pComponent, std::shared_ptr<GameObject>& pSender);
	RemovedComponentMessage(const RemovedComponentMessage&);
	RemovedComponentMessage(RemovedComponentMessage&&); //exchange members here;
	~RemovedComponentMessage() = default;

	//Accessors
public:

	ComponentType GetCompType() const { return mComponentType; }
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	RemovedComponentMessage& operator=(const RemovedComponentMessage& pOther){ return *this = RemovedComponentMessage(pOther); }

	RemovedComponentMessage& operator=(const RemovedComponentMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
	ComponentType mComponentType;
	
};

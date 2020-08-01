#pragma once
#include "Message.h"
#include "ComponentTypes.h"


class AddedComponentMessage : public Message {

	//Structors
public:
	AddedComponentMessage(ComponentType& pComponent, std::shared_ptr<GameObject>& pSender);
	AddedComponentMessage(const AddedComponentMessage&);
	AddedComponentMessage(AddedComponentMessage&&); //exchange members here;
	~AddedComponentMessage() = default;

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
	AddedComponentMessage& operator=(const AddedComponentMessage& pOther){ return *this = AddedComponentMessage(pOther); }

	AddedComponentMessage& operator=(const AddedComponentMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	ComponentType mComponentType;
	
};

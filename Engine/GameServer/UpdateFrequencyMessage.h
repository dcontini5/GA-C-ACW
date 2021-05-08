#pragma once
#include "Message.h"
#include "PyramidMessageTypes.h"
#include "SystemTypes.h"

class UpdateFrequencyMessage : public Message{

	//Structors
public:
	UpdateFrequencyMessage(const SystemType& pSystem, const short& pFrequency): Message(PyramidMessageTypes::UPDATE_FREQUENCY), mSystem(pSystem), mFrequency(pFrequency) {}
	UpdateFrequencyMessage(const UpdateFrequencyMessage&);
	UpdateFrequencyMessage(UpdateFrequencyMessage&&); //exchange members here;
	~UpdateFrequencyMessage() = default;

	//Accessors
public:
	
	SystemType GetSystemType() const { return mSystem; }
	int GetFrequency() const { return mFrequency; }
	//Mutators
public:
	
	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	UpdateFrequencyMessage& operator=(const UpdateFrequencyMessage& pOther){ return *this = UpdateFrequencyMessage(pOther); }

	UpdateFrequencyMessage& operator=(const UpdateFrequencyMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	SystemType mSystem;
	short mFrequency;
};

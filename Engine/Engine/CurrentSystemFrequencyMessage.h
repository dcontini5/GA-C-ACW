#pragma once
#include "Message.h"
#include "SystemTypes.h"

class CurrentSystemFrequencyMessage : public Message {

	//Structors
public:
	CurrentSystemFrequencyMessage(const SystemType& pSystem, const float& pCurrentFrequency): Message(MessageTypes::CURRENT_SYSTEM_FREQUENCY), mSystem(pSystem), mCurrentFrequency(pCurrentFrequency){}
	CurrentSystemFrequencyMessage(const CurrentSystemFrequencyMessage&);
	CurrentSystemFrequencyMessage(CurrentSystemFrequencyMessage&&); //exchange members here;
	~CurrentSystemFrequencyMessage() = default;

	//Accessors
public:

	SystemType GetSystemType() const { return mSystem; }
	float GetFrequency() const { return mCurrentFrequency; }
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	CurrentSystemFrequencyMessage& operator=(const CurrentSystemFrequencyMessage& pOther) = delete;

	CurrentSystemFrequencyMessage& operator=(const CurrentSystemFrequencyMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	SystemType mSystem;
	float mCurrentFrequency;
	
};

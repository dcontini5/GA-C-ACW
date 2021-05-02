#pragma once
#include "InputState.h"
#include "Message.h"


class InputStateMessage : public Message{

	//Structors
public:
	InputStateMessage(const InputState& pState) : Message(MessageTypes::INPUT_STATE), mState(pState){}
	InputStateMessage(const InputStateMessage&);
	InputStateMessage(InputStateMessage&&); //exchange members here;
	~InputStateMessage() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	InputStateMessage& operator=(const InputStateMessage& pOther) = delete;

	InputStateMessage& operator=(const InputStateMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	InputState mState{};
	
};

#pragma once
#include "MessageTypes.h"

class Message {

	//Structors
public:
	Message(MessageType& pType) : mType(pType){}
	Message(const Message&);
	Message(Message&&); //exchange members here;
	~Message() = default;

	//Accessors
public:
	MessageType GetType() const { return mType; }
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	Message& operator=(const Message& pOther){ return *this = Message(pOther); }

	Message& operator=(const Message&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	MessageType mType;
	
};

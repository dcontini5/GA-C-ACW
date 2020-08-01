#pragma once
#include <memory>

#include "MessageTypes.h"

class GameObject;


class Message {

	//Structors
public:
	Message(MessageType& pType, std::shared_ptr<GameObject>& pSender) : mType(pType), mSender(pSender){}
	Message(MessageType& pType) : mType(pType), mSender(nullptr){}
	Message(const Message&);
	Message(Message&&); //exchange members here;
	~Message() = default;

	//Accessors
public:
	MessageType GetType() const { return mType; } 
	std::shared_ptr<GameObject> GetSender() const { return mSender; }
	 
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
	std::shared_ptr<GameObject> mSender;
	
};

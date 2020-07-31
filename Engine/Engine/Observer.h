#pragma once
#include <memory>
#include "Message.h"

class Observer {

	//Structors
public:
	Observer() = default;
	Observer(const Observer&);
	Observer(Observer&&); //exchange members here;
	~Observer() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void OnMessage(std::shared_ptr<Message>& pMessage) = 0;
	
	// Private Functions
private:

	//Operators
public:
	Observer& operator=(const Observer& pOther) = delete;

	Observer& operator=(const Observer&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
};

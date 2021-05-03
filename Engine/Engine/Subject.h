#pragma once
#include <memory>
#include <map>
#include <vector>
#include "MessageTypes.h"


class Observer;
class Message;

typedef std::map<MessageType, std::vector<std::shared_ptr<Observer>>> ListenerMap;
typedef std::map<MessageType, std::vector<std::shared_ptr<Observer>>>::iterator ListenerMapIterator;

class Subject {

	//Structors
public:
	Subject() = default;	
	Subject(const Subject&);
	Subject(Subject&&); //exchange members here;
	~Subject() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Register(MessageType& pType , std::shared_ptr<Observer>& pObserver);
	virtual void Unregister(MessageType& pType, std::shared_ptr<Observer>& pObserver);
	virtual void OnMessage(std::shared_ptr<Message>& pMessage);
	// Private Functions
private:

	//Operators
public:
	
	Subject& operator=(const Subject& pOther) = delete;

	Subject& operator=(const Subject&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	ListenerMap mListeners;
	
};

#pragma once
#include <vector>

#include "Message.h"

typedef std::shared_ptr<GameObject> GameObjectPtr;

class ResetSceneMessage : public Message {

	//Structors
public:
	ResetSceneMessage(std::vector<GameObjectPtr>& pGameObjects): Message(MessageTypes::RESET_SCENE), mGameObjects(std::move(pGameObjects)){}
	ResetSceneMessage(): Message(MessageTypes::RESET_SCENE){}
	ResetSceneMessage(const ResetSceneMessage&);
	ResetSceneMessage(ResetSceneMessage&&); //exchange members here;
	~ResetSceneMessage() = default;

	//Accessors
public:

	std::vector<GameObjectPtr>& GetGameObjects() { return mGameObjects; }
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	ResetSceneMessage& operator=(const ResetSceneMessage& pOther){ return *this = ResetSceneMessage(pOther); }

	ResetSceneMessage& operator=(const ResetSceneMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	std::vector<GameObjectPtr> mGameObjects;
	
};

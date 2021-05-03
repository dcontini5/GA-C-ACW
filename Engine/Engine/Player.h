#pragma once
#include "GameObject.h"

class Player : public GameObject {

	//Structors
public:
	Player() :GameObject(){}
	Player(const Player&);
	Player(Player&&); //exchange members here;
	~Player() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void OnMessage(std::shared_ptr<Message>& pMessage) override;
	// Private Functions
private:

	//Operators
public:
	Player& operator=(const Player& pOther) = default;
	
	Player& operator=(const Player&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
};

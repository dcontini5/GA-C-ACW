#pragma once
#include "Game.h"


class ServersideGame : public Game {

	//Structors
public:
	ServersideGame() = default;
	ServersideGame(const ServersideGame&);
	ServersideGame(ServersideGame&&); //exchange members here;
	~ServersideGame() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Initialize(std::shared_ptr<Window>& pWindow) override;
	// Private Functions
private:

	//Operators
public:
	ServersideGame& operator=(const ServersideGame& pOther){ return *this = ServersideGame(pOther); }

	ServersideGame& operator=(const ServersideGame&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

};

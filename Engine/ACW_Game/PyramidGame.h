#pragma once
#include "Game.h"


class PyramidGame : public Game {

	//Structors
public:
	PyramidGame() = default;
	PyramidGame(const PyramidGame&);
	PyramidGame(PyramidGame&&); //exchange members here;
	~PyramidGame() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Initialize();
	// Private Functions
private:

	//Operators
public:
	PyramidGame& operator=(const PyramidGame& pOther){ return *this = PyramidGame(pOther); }

	PyramidGame& operator=(const PyramidGame&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

};

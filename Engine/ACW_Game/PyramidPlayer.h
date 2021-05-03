#pragma once
#include "Player.h"

class PyramidPlayer :public Player {

	//Structors
public:
	PyramidPlayer();
	PyramidPlayer(const PyramidPlayer&);
	PyramidPlayer(PyramidPlayer&&); //exchange members here;
	~PyramidPlayer();

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
	PyramidPlayer& operator=(const PyramidPlayer& pOther){ return *this = PyramidPlayer(pOther); }

	PyramidPlayer& operator=(const PyramidPlayer&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
};

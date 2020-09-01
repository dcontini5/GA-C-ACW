#pragma once
#include "Scene.h"

class PyramidScene :public Scene{

	//Structors
public:
	PyramidScene() = default;
	PyramidScene(const PyramidScene&);
	PyramidScene(PyramidScene&&); //exchange members here;
	~PyramidScene() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	virtual void Start();
	
	// Private Functions
private:

	//Operators
public:
	PyramidScene& operator=(const PyramidScene& pOther){ return *this = PyramidScene(pOther); }

	PyramidScene& operator=(const PyramidScene&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

};

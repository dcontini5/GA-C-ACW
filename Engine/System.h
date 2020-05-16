#pragma once
#include <memory>

class System {

	//Structors
public:
	System();
	virtual ~System();
	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	//todo add parameters
	virtual void Process(/* Components, deltatime? */) = 0;
	// Private Functions
private:

	//Data:
private:
	
};

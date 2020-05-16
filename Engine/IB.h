#pragma once
#include <memory>
#include "Renderer.h"

//Index Buffer Class
class IB {

	//Structors
public:
	IB();
	~IB();
	
	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	virtual void Create(const std::shared_ptr<Renderer>& pRenderer, const std::vector<WORD>& pIndices);
	
	// Private Functions
private:

	//Data:
private:
};

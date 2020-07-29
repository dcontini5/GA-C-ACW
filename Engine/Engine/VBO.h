#pragma once
#include <string>

#include "Renderer.h"

class VBO {

	//Structors
public:
	VBO():mNumVertices(0) {}
	VBO(const VBO&);
	VBO(VBO&&); //exchange members here;
	virtual ~VBO() = default;

	//Accessors
public:

	//Mutators
public:
	
	// Public Functions
public:
	virtual void Create(std::shared_ptr<Renderer>& pRenderer , const std::string& pMeshName) = 0;
	virtual void Draw() = 0;
	

	// Private Functions
private:

	//Operators
public:
	VBO& operator=(const VBO& pOther) = delete;
	VBO& operator=(const VBO&& pOther) = delete;

	//Data:
private:

	int mNumVertices;

	
};

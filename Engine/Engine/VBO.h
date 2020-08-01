#pragma once
#include <string>
#include <vector>

#include "ResourceManager.h"
#include "Renderer.h"


typedef std::vector<SimpleVertex> Vertices;
typedef std::vector<WORD> Indices;


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
	virtual void Create(std::shared_ptr<Renderer>& pRenderer, const Vertices& pVertices, const Indices& pIndices) = 0;
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

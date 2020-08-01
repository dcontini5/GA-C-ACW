#pragma once
#include <memory>
#include <string>
#include <vector>

#include "VBO.h"


class Mesh {

	//Structors
public:
	Mesh(const Vertices& pVertices,const Indices& pIndices) : mVertices(pVertices), mIndices(pIndices){}
	Mesh(const Mesh&);
	Mesh(Mesh&&); //exchange members here;
	~Mesh() = default;

	//Accessors
public:
	std::shared_ptr<VBO> GetVBO() const { return mVBO; }
	//Mutators
public:

	// Public Functions
public:
	void CreateVBO(std::shared_ptr<Renderer>& pRenderer);
	// Private Functions
private:

	//Operators
public:
	Mesh& operator=(const Mesh& pOther){ return *this = Mesh(pOther); }

	Mesh& operator=(const Mesh&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	std::shared_ptr<VBO> mVBO = nullptr;
	Vertices mVertices;
	Indices mIndices;
	
};

#pragma once
#include <memory>
#include <string>

#include "VBO.h"

class Mesh {

	//Structors
public:
	Mesh();
	Mesh(const Mesh&);
	Mesh(Mesh&&); //exchange members here;
	~Mesh();

	//Accessors
public:
	std::shared_ptr<VBO> GetVBO() const { return mVBO; }
	//Mutators
public:

	// Public Functions
public:
	void CreateVBO(std::shared_ptr<Renderer>& pRenderer, const std::string& pMeshName);
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
	
};

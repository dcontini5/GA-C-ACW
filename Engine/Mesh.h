#pragma once
#include <memory>
#include "VBO.h"
#include "IB.h"
#include "Renderer.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <apiquery2.h>

typedef std::vector<Vertex> Vertices;
typedef std::vector<WORD> Indices;



class Mesh {

	//Structors
public:
	Mesh();
	~Mesh() = default;
	//Accessors
public:
	VBO* GetVBO() { return mVBO.get(); }
	IB* GetIB() { return mIB.get(); }
	//std::shared_ptr<VBO> GetVBO() const { return mVBO; }
	//std::shared_ptr<IB> GetIB() const { return mIB; }
 	//Mutators
public:

	// Public Functions
public:
	
	void CreateResources(const std::shared_ptr<Renderer>& pRenderer);
	void LoadFromFile(const std::string& pFileName);

	
	// Private Functions
private:

	//Data:
private:

	Vertices mVertices;
	Indices mIndices;	
	std::unique_ptr<VBO> mVBO;
	std::unique_ptr<IB> mIB;
	//std::shared_ptr<VBO> mVBO;
	//std::shared_ptr<IB> mIB;
	
};

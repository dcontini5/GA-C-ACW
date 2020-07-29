#pragma once
#include <Windows.h>
//#include "Mesh.h"
#include <glm.hpp>
#include <memory>

class Mesh;

class Renderer {

	//Structors
public:
	Renderer(const UINT& pHeight, const UINT& pWidth) : mHeight(pHeight), mWidth(pWidth){}
	Renderer(const Renderer&);
	Renderer(Renderer&&); //exchange members here;
	virtual ~Renderer() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Render(std::shared_ptr<Mesh>& pMesh,const glm::vec3 pPos,const glm::vec3 pScale) = 0;
	virtual void InitRenderer() = 0;
	virtual void Cleanup() = 0;
	virtual void Run() = 0;
	virtual void StopRunning() = 0;
	
	// Private Functions
private:

	//Operators
public:
	Renderer& operator=(const Renderer& pOther) = delete;

	Renderer& operator=(const Renderer&& pOther) = delete;

	//Data:
protected:
	UINT mHeight;
	UINT mWidth;
};

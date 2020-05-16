#pragma once
#include "Renderer.h"
#include "Vertex.h"
#include "vector"

class VBO
{
	//Structors
public:
	VBO();
	~VBO() = default;

	//Functions
public:
	//virtual void Draw() = 0;
	virtual void Create(const Renderer* pRenderer, const std::vector<Vertex> pVertices) = 0;

	
};


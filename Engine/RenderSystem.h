#pragma once
#include "Renderer.h"
#include "System.h"

class RenderSystem : public System {

	//Structors
public:
	RenderSystem() : System(){}
	~RenderSystem() = default;
	
	//Accessors
public:

	
	//Mutators
public:

	
	// Public Functions
public:

	
	// Private Functions
private:

	//Data:
private:
	std::unique_ptr<Renderer> mUniqueRenderer = nullptr;
	std::shared_ptr<Renderer> mSharedRenderer = nullptr;
};

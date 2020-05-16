#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"

class Renderer {

	//Structors
public:
	Renderer();
	~Renderer();
	
	//Accessors
public:
	glm::vec4 GetClearColor() const { return mColor; }
	
	//Mutators
public:
	void SetClearColor(const glm::vec4 pColor) { mColor = pColor; }
	
	// Public Functions
public:
	virtual void ClearScreen() = 0;
	virtual void Draw(const Mesh* pMesh, glm::mat4 pMVM, const glm::vec4 pColor) = 0;
	//TODO: Uncomment Draw Overload
	//virtual void Draw(RenderComponent* pRC, glm::mat4 pMVM);

	virtual void Destroy() = 0;

	virtual void Initialize() = 0;

	virtual void SwapBuffers() = 0;

	
	// Private Functions
private:

	//Data:
private:
	glm::vec4 mColor;
	
};

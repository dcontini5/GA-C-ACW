#pragma once
#include <Windows.h>
//#include "Mesh.h"
#include <glm.hpp>
#include <memory>
#include <memory>
#include "UI.h"
#include "../ACW_Game/ClientUI.h"


class Mesh;
typedef  std::unique_ptr<UI> UIuniquePtr;

class Renderer {

	//Structors
public:
	Renderer(const UINT& pHeight, const UINT& pWidth) : mHeight(pHeight), mWidth(pWidth){}
	Renderer(const UINT& pHeight, const UINT& pWidth, UIuniquePtr& pUI) : mHeight(pHeight), mWidth(pWidth), mUI(std::move(pUI)){}
	Renderer(const Renderer&);
	Renderer(Renderer&&); //exchange members here;
	virtual ~Renderer() = default;

	//Accessors
public:

	//Mutators
public:
	void SetUI(UIuniquePtr& pUI) { mUI = std::move(pUI); }
	
	// Public Functions
public:
	virtual void Render(std::shared_ptr<Mesh>& pMesh,const glm::vec3 pPos,const glm::vec3 pScale) = 0;
	virtual void InitRenderer() = 0;
	virtual void Cleanup() = 0;
	virtual void Run() = 0;
	virtual void StopRunning() = 0;
	virtual void ClearScreen() = 0;
	virtual void Present() = 0;
	virtual void InitUi() = 0;
	virtual void RenderUI() = 0;
	
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
	UIuniquePtr mUI;
	
};

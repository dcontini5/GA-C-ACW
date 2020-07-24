#pragma once
#include <memory>

#include "Renderer.h"

class Window {

	//Structors
public:
	Window(const UINT& pHeight, const UINT& pWidth):mHeight(pHeight), mWidth(pWidth){}
	Window(const Window&);
	Window(Window&&); //exchange members here;
	~Window() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Initialize() = 0;
 	
	// Private Functions
private:

	//Operators
public:
	Window& operator=(const Window& pOther) = delete;

	Window& operator=(const Window&& pOther) = delete;

	//Data:
protected:
	UINT mHeight = 0;
	UINT mWidth = 0;

	std::shared_ptr<Renderer> mRenderer = nullptr;
	
};

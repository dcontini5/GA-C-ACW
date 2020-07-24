#pragma once
#include <Windows.h>


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
	virtual void Render() = 0;
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

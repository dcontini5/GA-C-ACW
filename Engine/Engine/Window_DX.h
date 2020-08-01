#pragma once

#include <Windows.h>
#include <d3d11_1.h>

#include "Resource.h"
#include "Window.h"
#include "Renderer_DX.h"

class Window_DX final : public Window {

	//Structors
public:
	
	Window_DX(const UINT& pHeight, const UINT& pWidth, std::shared_ptr<Game>& pGame, HINSTANCE pHInstance, int pNCmdShow);
	Window_DX(const Window_DX&);
	Window_DX(Window_DX&&); //exchange members here;
	~Window_DX() = default;

private:
	//Window_DX(const UINT& pHeight, const UINT& pWidth) : Window(pHeight, pWidth){}
	
	//Accessors
public:
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	Window_DX& operator=(const Window_DX& pOther) = delete;

	Window_DX& operator=(const Window_DX&& pOther) = delete;
	
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


	
	void Initialize() override;
	void InitPlaformSpecific(HINSTANCE pHInstance, int pNCmdShow);
	void InitPlaformSpecific();

	void Run();
	
	//Data:
private:

	HINSTANCE mHInstance = nullptr;
	HWND      mHWindow = nullptr;
	int		  mNCmdShow;

	
};

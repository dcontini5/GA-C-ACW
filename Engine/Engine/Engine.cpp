// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.


//int main()
//{
//    
//	auto TM = ThreadManager::Instance();
//
//	stuff a{};
//	
//	auto id = TM->AddThread(&stuff::print, a);
//	TM->TeminateThread(id);
//
//	
//}



#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include "Window_DX.h"
#include "ThreadManager.h"


DX_Renderer* renderer = nullptr;
Window_DX* window = nullptr;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//-------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	window = new Window_DX(600, 800);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	window->InitWindowDX(hInstance, nCmdShow);
	window->Initialize();

	auto renderer = window->getRenderer();

	auto tm = ThreadManager::Instance();
	//if (FAILED(InitDevice()))
	//{
	//	CleanupDevice();
	//	return 0;
	//}

	// Main message loop

   
	//MSG msg = { 0 };
	//while (WM_QUIT != msg.message)
	//{
	//	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//	
	//	
	//}

	

	
	//auto i = tm->AddThread(&Renderer::Run, renderer);
	auto i = tm->AddThread(&Window_DX::Run, window);
	//
	
	tm->TeminateThread(i);
	
	//CleanupDevice();
	renderer->Cleanup();
	
	return 0;
	//return (int)msg.wParam;
}

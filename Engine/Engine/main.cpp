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
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	
	window = new Window_DX(600, 800, hInstance, nCmdShow);

	
	auto tm = ThreadManager::Instance();

	const auto windowThreadID = tm->AddThread(&Window_DX::Run, window);

	//todo auto game = new Game();
	//game.Run();

	

	tm->TeminateThread(windowThreadID);
	
	return 0;
}


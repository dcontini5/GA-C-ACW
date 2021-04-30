#include "Window_DX.h"
#include "ThreadManager.h"
#include "Game.h"


Window_DX::Window_DX(const UINT& pHeight, const UINT& pWidth, std::shared_ptr<Game>& pGame, HINSTANCE pHInstance, int pNCmdShow)
: Window(pHeight, pWidth, pGame), mHInstance(pHInstance), mNCmdShow(pNCmdShow){
	
	
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK Window_DX::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Window_DX::Initialize(){

	InitPlaformSpecific();
	
	mRenderer = std::make_shared<DX_Renderer>(mHWindow, mHeight, mWidth);
	mRenderer->InitRenderer();


	
}


void Window_DX::InitPlaformSpecific(HINSTANCE pHInstance, int pNCmdShow) {

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = pHInstance;
	wcex.hIcon = LoadIcon(pHInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
	if (!RegisterClassEx(&wcex)) return;

	// Create window
	// 
	//mHInstance = pHInstance;
	RECT rc = { 0, 0, static_cast<LONG> (mWidth), static_cast<LONG> (mHeight) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	mHWindow = CreateWindow(L"TutorialWindowClass", L"GA&C Window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, pHInstance,
		nullptr);

	ShowWindow(mHWindow, pNCmdShow);

}

void Window_DX::InitPlaformSpecific(){


	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mHInstance;
	wcex.hIcon = LoadIcon(mHInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
	if (!RegisterClassEx(&wcex)) return;

	// Create window
	// 
	//mHInstance = pHInstance;
	RECT rc = { 0, 0, static_cast<LONG> (mWidth), static_cast<LONG> (mHeight) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	mHWindow = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 4: 3D Spaces",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, mHInstance,
		nullptr);

	ShowWindow(mHWindow, mNCmdShow);

	
}

void Window_DX::Run() {

	Initialize();

	auto wind = shared_from_this();
	
	mGame->Initialize(wind);
	
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

}

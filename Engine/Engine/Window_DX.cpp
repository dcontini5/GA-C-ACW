#include "Window_DX.h"
#include "ThreadManager.h"
#include "Game.h"
#include "windowsx.h"

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



	RECT rcClient;                 // client area rectangle 
	static POINT ptClientUL;              // client upper left corner
	// 
	static POINTS ptsBegin;        // beginning point 
	static POINTS ptsEnd;
	////static POINTS ptsBeginLMouse;        // beginning point 
	//static POINTS ptsEndLMouse;      // previous endpoint 
	//static POINTS ptsBeginRMouse;
	//static POINTS ptsEndRMouse;
	
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
	{
		InputState state;
		state.key = wParam;
		state.keyState = true;
		Game::Instance()->OnKeyboard(state);
		return 0;
	}

	case WM_KEYUP:
	{
		InputState state;
		state.key = wParam;
		state.keyState = false;
		Game::Instance()->OnKeyboard(state);
		return 0;
	}
	
	case WM_LBUTTONDOWN:

	{
		//SetCapture(hWnd);

		GetClientRect(hWnd, &rcClient);
		ptClientUL.x = rcClient.left;
		ptClientUL.y = rcClient.top;
			
		ClientToScreen(hWnd, &ptClientUL); 

		ptsBegin = MAKEPOINTS(lParam);
		ptsEnd = ptsBegin;
		ShowCursor(false);
		return 0;

	}

	case WM_RBUTTONDOWN:

	{
		//SetCapture(hWnd);

		GetClientRect(hWnd, &rcClient);
		ptClientUL.x = rcClient.left;
		ptClientUL.y = rcClient.top;



		ClientToScreen(hWnd, &ptClientUL);

		ptsBegin = MAKEPOINTS(lParam);
		ptsEnd = ptsBegin;
		ShowCursor(false);
		return 0;

	}
	case  WM_MOUSEMOVE:
		{


			if (wParam & MK_LBUTTON)
			{
				
				const auto ptsCurr = MAKEPOINTS(lParam);


				
				InputState state;

				state.key = WM_LBUTTONDOWN;
				state.keyState = wParam & MK_LBUTTON && !(wParam & MK_RBUTTON);
				auto x = wParam & MK_LBUTTON && !(wParam & MK_RBUTTON);
				state.mouseMov.x = ptsEnd.x - ptsCurr.x;
				state.mouseMov.y = ptsEnd.y - ptsCurr.y;

				Game::Instance()->OnKeyboard(state);
				ptsEnd = ptsCurr;
				
			}
			
			if (wParam & MK_RBUTTON)
			{

				const auto ptsCurr = MAKEPOINTS(lParam);

				InputState state;

				state.key = WM_RBUTTONDOWN;
				state.keyState = !(wParam & MK_LBUTTON) && (wParam & MK_RBUTTON);
				auto x = !(wParam & MK_LBUTTON) && (wParam & MK_RBUTTON);
				state.mouseMov.x = ptsEnd.x - ptsCurr.x;
				state.mouseMov.y = ptsEnd.y - ptsCurr.y;

				Game::Instance()->OnKeyboard(state);
				ptsEnd = ptsCurr;
				
			}

			return 0;
			
			
		}

	case WM_LBUTTONUP:
		{

		//ClipCursor(nullptr);
		//ReleaseCapture();
		//hdc = GetDC(hWnd);
		InputState state;
			
		state.key = WM_LBUTTONDOWN;
		state.keyState = false;

		Game::Instance()->OnKeyboard(state);
			
		SetCursorPos(ptsBegin.x + ptClientUL.x, ptsBegin.y + ptClientUL.y);
		ShowCursor(true);
		return 0;
		}

	case WM_RBUTTONUP:
	{

		//ClipCursor(nullptr);
		//ReleaseCapture();
		//hdc = GetDC(hWnd);
		InputState state;

		state.key = WM_RBUTTONDOWN;
		state.keyState = false;

		Game::Instance()->OnKeyboard(state);

		SetCursorPos(ptsBegin.x + ptClientUL.x, ptsBegin.y + ptClientUL.y);
		ShowCursor(true);
		return 0;
			
	}
		
		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

	case WM_MOUSEWHEEL:
		{
			InputState state;

			state.key = WM_MOUSEWHEEL;
			state.keyState = true;
			state.wheelRot = static_cast<int8_t>(GET_WHEEL_DELTA_WPARAM(wParam) * 0.00833333333333333333333333333333);
			
			Game::Instance()->OnKeyboard(state);	
			return 0;
		}
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
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

#include "GEViewImpl.h"

GEViewImpl::GEViewImpl()
{

}

GEViewImpl::~GEViewImpl()
{

}

GEViewImpl* GEViewImpl::create( const std::string viewName )
{
	return create(viewName, Size(800, 600));
}

GEViewImpl* GEViewImpl::create( const std::string viewName, Size size )
{
	auto view = new (std::nothrow) GEViewImpl;
	if (view && view->initWithRect(viewName, size))
	{
		return view;
	}
	return nullptr;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_PAINT:
		ValidateRect(hwnd, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

bool GEViewImpl::initWithRect( const std::string viewName, Size size )
{
	setViewName(viewName);

	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "GearEngine";
	
	if (!RegisterClassEx(&wndClass))
	{
		return false;
	}

	HWND hwnd = CreateWindow("GearEngine", viewName.c_str(), WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
		CW_USEDEFAULT, CW_USEDEFAULT, int(size.width), int(size.height), NULL, NULL, wndClass.hInstance, NULL);
	
	RECT windowRect, clientRect;
	GetWindowRect(hwnd, &windowRect);
	GetClientRect(hwnd, &clientRect);
	int w = windowRect.right - windowRect.left + int(size.width) - clientRect.right;
	int h = windowRect.bottom - windowRect.top + int(size.height) - clientRect.bottom;
	int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
	MoveWindow(hwnd, x, y, w, h, true);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = { 0 };
	while(msg.message != WM_QUIT)
	{
		if( PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(1);
		}
	}

	UnregisterClass("GearEngine", wndClass.hInstance);

	return true;
}
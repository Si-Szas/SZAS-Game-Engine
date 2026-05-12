#include "Window.h"

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Order matters in passing attributes of wc, or else it gives us an error
	switch (uMsg)
	{
		//Window Creation Event
		case WM_CREATE:
		{
			//Window creation is collected
			Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			//Stored for later look up
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
			
			window->onCreate();
			break;
		}
		//Window Destroy Event
		case WM_DESTROY:
		{
			//Window made a request to terminate
			Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		//Default, pass all parameters
		default: return::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
	//Window Procedure
	 //Handles events of our window, like creation and destroy events

	//Register a Class that defines properties regarding style and visual appearance
	// - CONDITIONAL
	//		- If Window wasn't created properly, return false 
	// */
	if (!::RegisterClassEx(&wc)) return false;

	//Creates Window
	m_hWnd = ::CreateWindowEx
	(
		WS_EX_OVERLAPPEDWINDOW,
		L"MyWindowClass",			//Class Name assigned earlier
		L"DirectX Application",		//Window Name
		WS_EX_OVERLAPPEDWINDOW,		//Window Style
		CW_USEDEFAULT,				//Window Position
		CW_USEDEFAULT,				//Window Position
		1024,						//Window Width
		768,						//Window Height
		NULL,
		NULL,
		NULL,
		this
	);
	
	//If window creation fails, return false
	if (!m_hWnd) return false;

	//Make window show up
	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd);
	
	//Indicates that the window is running
	m_isRunning = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->onUpdate();

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return m_isRunning;
}

bool Window::release()
{
	//Destroy Window
	if (!::DestroyWindow(m_hWnd)) return false;

	return true;
}

void Window::onCreate()
{

}

void Window::onUpdate()
{

}

void Window::onDestroy()
{
	m_isRunning = false;
}

Window::~Window()
{
}

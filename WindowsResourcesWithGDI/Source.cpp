#define WIN32_LEAN_AND_MEAN

#include <windows.h> // Include all the windows headers
#include <windowsx.h> // Include useful macros
#include "resource.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

void GameLoop()
{
	// One frame of game logic occurs here...
}

LRESULT CALLBACK WindowProc(
	HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system
	PAINTSTRUCT ps; // Used in WM_PAINT
	HDC hdc; // Handle to a device context

	// What is the message
	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here


		// Return Success
		return (0);
	}
	break;
	case WM_PAINT:
	{
		// Simple validate the window
		hdc = BeginPaint(_hwnd, &ps);

		// You would do all your painting here...

		EndPaint(_hwnd, &ps);

		// Return Success
		return (0);
	}
	break;
	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT
		PostQuitMessage(0);

		// Return Sucess
		return(0);
	}
	break;
	default:
		break;
	} // End swicth

	// Processo any messages that we did not take care of...
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));

}

int WINAPI WinMain(
	HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.
	HCURSOR hCrosshair = LoadCursor(_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));


	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registr the window class
	if (!RegisterClassEx(&winclass))
	{
		return(0);
	}

	// Create the window
	hwnd = CreateWindowEx(
		NULL, // Extended style
		WINDOW_CLASS_NAME, // Class
		L"My first Window", // Title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, // Initial x, y
		400, 400, // Initial width, height
		NULL, // Handle to parent
		NULL, // Handle to menu
		_hInstance, // Instance of this application
		NULL // Extra creation parameters
	);

	if (!(hwnd))
	{
		return (0);
	}

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// Translate any accelerator keys
			TranslateMessage(&msg);
		}

		// Main game processing goes here
		GameLoop(); // One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}
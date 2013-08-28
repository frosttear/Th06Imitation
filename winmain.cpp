//--------------------------------------------------------------------------------------
//File: winmain.cpp
//
//Desc: 
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include "GameManager.h"
#include "resource.h"
using namespace std;

#define SCR_WIDTH 640
#define SCR_HEIGHT 512
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif
//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
HINSTANCE					hInst;				// holds the instance for this app
HWND						wndHandle;					// global window handle
bool						bFullScreen = false;
//--------------------------------------------------------------------------------------
// forward declarations
//--------------------------------------------------------------------------------------
bool					initWindow(HINSTANCE hInstance);
LRESULT CALLBACK		WndProc(HWND, UINT, WPARAM, LPARAM);
void					CleanUp(void);
bool					AppInit(HINSTANCE,HWND hwnd);
//--------------------------------------------------------------------------------------
//WinMain 
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	
	// call our function to init and create our window
	if (!initWindow(hInstance))
	{
		MessageBox(NULL, "Unable to create window", "ERROR", MB_OK);
		return false;
	}
	
	if (!AppInit(hInstance, wndHandle))
		return false;
	ShowWindow(wndHandle, SW_SHOW);
	ShowCursor(FALSE);
	UpdateWindow(wndHandle);
	
	
	// Main message loop:
	// Enter the message loop
    MSG msg; 
    ZeroMemory( &msg, sizeof(msg) );
//	float delay = 0;
    while( msg.message!=WM_QUIT )
    {
		// check for messages
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }else
		{
			gm.Update ();
			gm.Render ();
		}
    }
	
	//shutdown the directx manager
	CleanUp();
	return (int) msg.wParam;
}


//--------------------------------------------------------------------------------------
// initWindow
// Creates the main application window
//--------------------------------------------------------------------------------------
bool initWindow(HINSTANCE hInstance)
{
//	HANDLE hImage = LoadImageA(hInstance, , 32, 32, 0);
	HICON hIcon = (HICON) LoadImageA(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 40, 40, LR_DEFAULTCOLOR);
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, (WNDPROC)WndProc,
			   0L, 0L,  hInstance, hIcon, NULL, NULL, NULL,
			   "Th06-like", NULL
		};

	RegisterClassEx(&wcex);
	DWORD dwWindowStyle;
	if (bFullScreen)
	{
		dwWindowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
	}else
	{
		dwWindowStyle = WS_OVERLAPPEDWINDOW;
	}
	
	wndHandle = CreateWindow("Th06-like",
							 "·Â¶«·½ºìÄ§Ïç", 
							 dwWindowStyle,
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 SCR_WIDTH, 
							 SCR_HEIGHT, 
							 NULL, 
							 NULL, 
							 hInstance, 
							 NULL);
   if (!wndHandle)
      return false;
   

   return true;
}


//--------------------------------------------------------------------------------------
// AppInit
// Init DX Devices
//--------------------------------------------------------------------------------------
bool AppInit(HINSTANCE hInst,HWND hwnd)
{
	// initialize DirectX
	if (!dxMgr.init(hwnd, bFullScreen))
	{
		MessageBox(NULL, "Unable to init DirectX", "ERROR", MB_OK);
		return false;
	}
	// initialize DirectInput
	if (!diMgr.initDirectInput(hInst,hwnd))
	{
		MessageBox(wndHandle, "Unalbe to init DirectInput", "ERROR", MB_OK);
		return false;
	}
	// initialize DirectSound
	if (!dsMgr.initDirectSound(hwnd))
	{
		MessageBox(NULL, "Unable to init DirectSound", "ERROR", MB_OK);
		return false;
	}
	return true;
}
//--------------------------------------------------------------------------------------
//WndProc
//The application's window procedure
//--
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		//case WM_PAINT:
		//	render();
		//	return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//--------------------------------------------------------------------------------------
// CleanUp
// Release devices and delete pointers
//--------------------------------------------------------------------------------------
void CleanUp()
{
	dxMgr.shutdown();
	dsMgr.shutdown();
	diMgr.shutdown();
}
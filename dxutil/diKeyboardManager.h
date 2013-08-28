/*******************************************************************
* DirectInput Keyboard Manager Class
*******************************************************************/
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80) 
#define KEYDOWN(name, key) (name[key] & 0x80) 
class diKeyboardManager
{
public:
	~diKeyboardManager(void);

	// singleton stuff
	static diKeyboardManager& getInstance() { static diKeyboardManager pInstance; return pInstance;}

	bool initDirectInput(HINSTANCE hInst, HWND wndHandle);
	bool isKeyPressed(int which);
	bool isAnyKeyPressed(void);
	void shutdown(void);

	void getInput(void);
	void GetBufferedInput(void);
	bool isKeyDown(int which);
	bool isKeyUp(int which);
	bool isKeyHold(int which);

/*	inline int getCurMouseX(void) { return mouseState.lX; }
	inline int getCurMouseY(void) { return mouseState.lY; }
	*/
private:
	diKeyboardManager(void);

	LPDIRECTINPUT8        g_lpDI;		// the direct input object
	LPDIRECTINPUTDEVICE8  g_lpDIDevice; // the direct input device

	char buffer[256];			// The current state of keyboard
	char oldBuffer[256];
	bool oldKeyDownBuffer[256];
	bool keyUpBuffer[256];
	bool keyDownBuffer[256];
};
static diKeyboardManager& diMgr	= diKeyboardManager::getInstance();
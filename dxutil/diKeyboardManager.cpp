//--------------------------------------------------------------------------------------
//File: diKeyboardManager.cpp
//
//Desc: class for getting keyboard input without buffers
//
//Copyright (c) Liu.zhenxing. All rights reserved.
//--------------------------------------------------------------------------------------
#include ".\diKeyboardManager.h"
#define	DINPUT_BUFFERSIZE 16
extern HINSTANCE hInst;				// holds the instance for this app

diKeyboardManager::diKeyboardManager(void)
{
	g_lpDI = NULL;
	g_lpDIDevice = NULL;
}

diKeyboardManager::~diKeyboardManager(void)
{
	shutdown();
}

/*******************************************************************
* initDirectInput
* Initializes DirectInput for use with a keyboard device
*******************************************************************/
bool diKeyboardManager::initDirectInput(HINSTANCE hInst, HWND wndHandle)
{
	HRESULT hr;

	// Create the DirectInput object. DIRECTINPUT_VERSION
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                            IID_IDirectInput8, (void**)&g_lpDI, NULL); 

	if FAILED(hr) return FALSE; 

    // Retrieve a pointer to an IDirectInputDevice8 interface 
    hr = g_lpDI->CreateDevice(GUID_SysKeyboard, &g_lpDIDevice, NULL); 

	hr = g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard); 

	if FAILED(hr) { 
		return FALSE; 
	} 

	// Set the cooperative level 
    hr = g_lpDIDevice->SetCooperativeLevel(wndHandle, 
                             DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
    if FAILED(hr) 
    { 
        return FALSE; 
    }
	//Set buffer size
	DIPROPDWORD     property;
    property.diph.dwSize = sizeof(DIPROPDWORD);
    property.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    property.diph.dwObj = 0;
    property.diph.dwHow = DIPH_DEVICE;
    property.dwData = DINPUT_BUFFERSIZE;

    hr = g_lpDIDevice->SetProperty(DIPROP_BUFFERSIZE, &property.diph);
    if FAILED(hr)
    {
        return FALSE;
    }
	//Get device
	g_lpDIDevice->Acquire(); 
    if FAILED(hr) 
    { 
        return FALSE; 
    } 

	return true;
}

/*******************************************************************
* shutdown
* Shuts down and releases DirectInput
*******************************************************************/
void diKeyboardManager::shutdown(void)
{
	if (g_lpDI) 
    { 
        if (g_lpDIDevice) 
        { 
			// Always unacquire device before calling Release(). 
            g_lpDIDevice->Unacquire(); 
            g_lpDIDevice->Release();
            g_lpDIDevice = NULL; 
        } 
        g_lpDI->Release();
        g_lpDI = NULL; 
    } 
}

/*******************************************************************
* getInput
* Retrieves the current user input
*******************************************************************/
void diKeyboardManager::getInput(void)
{
	HRESULT hr;
	hr = g_lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 

	// check the return state to see if the device is still accessible
	if (FAILED ( hr ))
	{
		// try and reacquire the input device
		hr = g_lpDIDevice->Acquire();
		// do a continuous loop until the device is reacquired
	       while( hr == DIERR_INPUTLOST ) 
			hr = g_lpDIDevice->Acquire();
	}
	for (int i = 0; i < 256; i ++)
	{
		oldKeyDownBuffer[i] = keyDownBuffer[i];
		if (buffer[i] & 0x80)
		{
			keyDownBuffer[i] = true;
		}else
		{
			keyDownBuffer[i] = false;
		}
	}
}

void diKeyboardManager::GetBufferedInput(void)
{
    DIDEVICEOBJECTDATA  didod[DINPUT_BUFFERSIZE];  // Receives buffered data
    DWORD               dwElements = DINPUT_BUFFERSIZE;
    HRESULT             hr;

    hr = DIERR_INPUTLOST;
	for (int i = 0; i < 256; i ++)
	{
		oldBuffer[i] = buffer[i];
		oldKeyDownBuffer[i] = keyDownBuffer[i];
		keyDownBuffer[i] = false;
		keyUpBuffer[i]	 = false;
	}
	for (DWORD i = 0; i < dwElements; i ++)
	{
		didod[i].dwSequence = 0;
	}
    hr = g_lpDIDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0);
    if (hr != DI_OK)
    {
        hr = g_lpDIDevice->Acquire();
		hr = g_lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    }
    for (DWORD i= 0; i < dwElements; i++)
    {
		if (didod[i].dwSequence != 0)
		{
			if ((didod[i].dwData & 0x80) == 0)
			{
				keyUpBuffer[didod[i].dwOfs] = true;
			}
			else
			{
				keyDownBuffer[didod[i].dwOfs] = true;
			}
		}
    }
  
}
/*******************************************************************
* isKeyDown
*******************************************************************/
bool diKeyboardManager::isKeyDown(int which)
{
	return keyDownBuffer[which];
}

bool diKeyboardManager::isAnyKeyPressed()
{
	for (int i =0 ; i < 255; i ++)
		if (isKeyDown(i))
			return true;
	return false;
}
bool diKeyboardManager::isKeyUp(int which)
{
	return keyUpBuffer[which];
}

bool diKeyboardManager::isKeyHold(int which)
{
	return (keyDownBuffer[which] && oldKeyDownBuffer[which]);
}

bool diKeyboardManager::isKeyPressed(int which)
{
	return (keyDownBuffer[which] && !oldKeyDownBuffer[which]);
}
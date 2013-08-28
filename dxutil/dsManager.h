#pragma once
//#include <dxerr9.h>
#include <dsound.h>
#include "dsutil.h"
#include <string>
//-----------------------------------------------------------------------------
// Typing macros 
//-----------------------------------------------------------------------------
#define DSOUND_StopSound(s)         { if(s) s->Stop(); }
#define DSOUND_PlaySound(s)         { if(s) s->Play( 0, 0 ); }
#define DSOUND_PlaySoundLooping(s)  { if(s) s->Play( 0, DSBPLAY_LOOPING ); }
class dsManager
{
public:
	~dsManager(void);
	static dsManager& getInstance() { static dsManager pInstance; return pInstance;}

	bool initDirectSound(HWND hwnd);
	void shutdown(void);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);
	// singleton stuff
	
inline LPDIRECTSOUND8 getDSDevice(void) { return m_pDS; }

private:

	LPDIRECTSOUND8		m_pDS;
	HRESULT				lastResult;

};
static dsManager& dsMgr					= dsManager::getInstance();
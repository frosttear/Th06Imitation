#include ".\dsManager.h"


dsManager::~dsManager(void)
{
}

/*******************************************************************
* shutdownDirectSound
* Releases the DirecSound device
*******************************************************************/
void dsManager::shutdown(void)
{
	if (m_pDS)
	{
		m_pDS->Release();
		m_pDS = NULL;
	}
}

/*******************************************************************
* initDirectSound
* Initializes DirectSound
*******************************************************************/
bool dsManager::initDirectSound(HWND hwnd)
{
	lastResult = DirectSoundCreate8( NULL, &m_pDS, NULL );
	if FAILED (lastResult)
		return false;

	// Set DirectSound cooperative level 
    lastResult = m_pDS->SetCooperativeLevel( hwnd, DSSCL_PRIORITY );
	if FAILED ( lastResult )
		return false;

	return true;
}

/*******************************************************************
* LoadWaveToSoundBuffer
* Loads a wave file into a DirectSound Buffer
*******************************************************************/
LPDIRECTSOUNDBUFFER dsManager::LoadWaveToSoundBuffer(std::string wavFilename)
{
	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
	CWaveFile *wavFile;

	wavFile = new CWaveFile();
	wavFile->Open((char*)wavFilename.c_str(), NULL, WAVEFILE_READ );
	if( wavFile->GetSize() == 0 )
	{
		MessageBox(NULL, ((std::string)("invalid file" + wavFilename)).c_str(), "ERROR", MB_OK);
		return NULL;
	}

	DSBUFFERDESC dsbd;
    ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
    dsbd.dwSize          = sizeof(DSBUFFERDESC);
    dsbd.dwFlags         = DSBCAPS_CTRLVOLUME;
    dsbd.dwBufferBytes   = wavFile->GetSize();
    dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat     = wavFile->m_pwfx;

	lastResult = m_pDS->CreateSoundBuffer( &dsbd, &apDSBuffer, NULL );
	if FAILED (lastResult)
	{
		MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
		return NULL;
	}

	VOID*   pDSLockedBuffer      = NULL; // Pointer to locked buffer memory
    DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
    DWORD   dwWavDataRead        = 0;    // Amount of data read from the wav file 
	//
	lastResult = apDSBuffer->Lock( 0, wavFile->GetSize(), 
						   &pDSLockedBuffer, &dwDSLockedBufferSize, 
                           NULL, NULL, 0L );
	if FAILED (lastResult)
        return NULL;

 //   // Reset the wave file to the beginning 
    wavFile->ResetFile();

	// Read the wave file
    lastResult = wavFile->Read( (BYTE*) pDSLockedBuffer,
                       dwDSLockedBufferSize, 
                       &dwWavDataRead );
	// Check to make sure that this was successful
	if FAILED (lastResult)
        return NULL;
    // Unlock the buffer, we don't need it anymore.
    apDSBuffer->Unlock( pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0 );

	// Clean up
	delete wavFile;

	return apDSBuffer;
}


/*******************************************************************
* playSound
* plays a sound currently in a buffer only once
*******************************************************************/
void dsManager::playSound(LPDIRECTSOUNDBUFFER whichBuffer)
{
	whichBuffer->Play( 0, 0, 0);
}

/*******************************************************************
* playSoundLoop
* plays a sound in a buffer repeatedly
*******************************************************************/
void dsManager::playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer)
{

	whichBuffer->Play( 0, 0, DSBPLAY_LOOPING );
}

/*******************************************************************
* stopSound
* stops the sound in this buffer from playing
*******************************************************************/
void dsManager::stopSound(LPDIRECTSOUNDBUFFER whichBuffer)
{
	whichBuffer->Stop();
}

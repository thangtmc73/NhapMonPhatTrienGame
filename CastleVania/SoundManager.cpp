#include "SoundManager.h"
#include "Global.h"
#include <mmsystem.h>
#include <dxerr.h>
#include <mmreg.h>
#include "dxutil.h"

CSoundManager* CSoundManager::_instance = NULL;

CSoundManager * CSoundManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CSoundManager();
	}
	return _instance;
}

GSound * CSoundManager::LoadSound(char * filename)
{
	HRESULT result;

	//create local reference to wave data
	GSound *wave;

	//attempt to load the wave file
	result = Create(&wave, filename);
	if (result != DS_OK)
	{
		GLTrace("[Failed] Can not load sound file");
		return NULL;
	}
	GLTrace("Sound file has been loaded");
	
	//return the wave
	return wave;
}

void CSoundManager::AddSoundToList(int a_index, GSound * a_sound)
{
	_listOfSounds[a_index] = a_sound;
}

void CSoundManager::PlaySoundWithIndex(int a_index)
{
	_listOfSounds[a_index]->Play();
	GLTrace("Sound file has been played");
}

void CSoundManager::LoopSoundWithIndex(int a_index)
{
	_listOfSounds[a_index]->Play(0, DSBPLAY_LOOPING);
}

void CSoundManager::StopSoundWithIndex(int a_index)
{
	_listOfSounds[a_index]->Stop();
}

HRESULT CSoundManager::SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate)
{
	HRESULT             hr;
	LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

	if (G_SoundManager == NULL)
		return CO_E_NOTINITIALIZED;;

	// Get the primary buffer 
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	if (FAILED(hr = G_SoundManager->CreateSoundBuffer(&dsbd, &pDSBPrimary, NULL)))
		return DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);

	WAVEFORMATEX wfx;
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
	wfx.nChannels = (WORD)dwPrimaryChannels;
	wfx.nSamplesPerSec = (DWORD)dwPrimaryFreq;
	wfx.wBitsPerSample = (WORD)dwPrimaryBitRate;
	wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
	wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);

	if (FAILED(hr = pDSBPrimary->SetFormat(&wfx)))
		return DXTRACE_ERR(TEXT("SetFormat"), hr);

	if (pDSBPrimary)
	{
		pDSBPrimary->Release();
		pDSBPrimary = NULL;
	};

	return S_OK;
}

bool CSoundManager::Init()
{
	HRESULT             hr;
	if (G_SoundManager)
	{
		G_SoundManager->Release();
		G_SoundManager = NULL;
	}

	// Create IDirectSound using the primary sound device
	if (FAILED(hr = DirectSoundCreate8(NULL, &G_SoundManager, NULL)))
		return DXTRACE_ERR(TEXT("DirectSoundCreate8"), hr);

	// Set DirectSound coop level 
	if (FAILED(hr = G_SoundManager->SetCooperativeLevel(G_hWnd, DSSCL_PRIORITY)))
		return DXTRACE_ERR(TEXT("SetCooperativeLevel"), hr);

	return S_OK;

	//set the primary buffer format
	HRESULT result = this->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
	{
		GLTrace("[FAILED] Can not set the primary buffer");
		return false;
	}
	GLTrace("Directx Sound has been success init");
	return true;
}

void CSoundManager::Release()
{
}

void CSoundManager::LoadAllSounds()
{
	AddSoundToList(eSoundIndex::LEVEL_1, LoadSound("Stage_01_Vampire_Killer.wav"));
	AddSoundToList(eSoundIndex::LEVEL_2, LoadSound("Stage_04_Stalker.wav"));
	AddSoundToList(eSoundIndex::GAME_OVER, LoadSound("Game_Over.wav"));
	AddSoundToList(eSoundIndex::GAME_START, LoadSound("Game_Start_Prologue.wav"));
	AddSoundToList(eSoundIndex::BOSS_BATTLE_POISON_MIND, LoadSound("Boss_Battle_Poison_Mind.wav"));
	AddSoundToList(eSoundIndex::LIFE_LOST, LoadSound("Life_Lost.wav"));
	AddSoundToList(eSoundIndex::STAGE_CLEAR, LoadSound("Life_Lost.wav"));
	AddSoundToList(eSoundIndex::TITLE_THEME, LoadSound("Title_Theme_Prelude.wav"));
	AddSoundToList(eSoundIndex::USING_WHIP, LoadSound("usingwhip.wav"));
	AddSoundToList(eSoundIndex::COLLECTING_ITEM, LoadSound("collectitem.wav"));
	AddSoundToList(eSoundIndex::COLLECTING_WEAPON, LoadSound("collectweapon.wav"));

}

CSoundManager::CSoundManager()
{
}

HRESULT CSoundManager::Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener)
{
	HRESULT             hr;
	DSBUFFERDESC        dsbdesc;
	LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

	if (ppDSListener == NULL)
		return E_INVALIDARG;
	if (G_SoundManager == NULL)
		return CO_E_NOTINITIALIZED;

	*ppDSListener = NULL;

	// Obtain primary buffer, asking it for 3D control
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	if (FAILED(hr = G_SoundManager->CreateSoundBuffer(&dsbdesc, &pDSBPrimary, NULL)))
		return DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);

	if (FAILED(hr = pDSBPrimary->QueryInterface(IID_IDirectSound3DListener,
		(VOID**)ppDSListener)))
	{
		if (pDSBPrimary)
		{
			pDSBPrimary->Release();
			pDSBPrimary = NULL;
		};
		return DXTRACE_ERR(TEXT("QueryInterface"), hr);
	}

	// Release the primary buffer, since it is not need anymore
	if (pDSBPrimary)
	{
		pDSBPrimary->Release();
		pDSBPrimary = NULL;
	};
	return S_OK;
}

HRESULT CSoundManager::Create(GSound ** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNumBuffers)
{
	HRESULT hr;
	HRESULT hrRet = S_OK;
	DWORD   i;
	LPDIRECTSOUNDBUFFER* apDSBuffer = NULL;
	DWORD                dwDSBufferSize = NULL;
	CWaveFile*           pWaveFile = NULL;

	if (G_SoundManager == NULL)
		return CO_E_NOTINITIALIZED;
	if (strWaveFileName == NULL || ppSound == NULL || dwNumBuffers < 1)
		return E_INVALIDARG;

	apDSBuffer = new LPDIRECTSOUNDBUFFER[dwNumBuffers];
	if (apDSBuffer == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto LFail;
	}

	pWaveFile = new CWaveFile();
	if (pWaveFile == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto LFail;
	}

	pWaveFile->Open(strWaveFileName, NULL, WAVEFILE_READ);

	if (pWaveFile->GetSize() == 0)
	{
		// Wave is blank, so don't create it.
		hr = E_FAIL;
		goto LFail;
	}

	// Make the DirectSound buffer the same size as the wav file
	dwDSBufferSize = pWaveFile->GetSize();

	// Create the direct sound buffer, and only request the flags needed
	// since each requires some overhead and limits if the buffer can 
	// be hardware accelerated
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = dwCreationFlags;
	dsbd.dwBufferBytes = dwDSBufferSize;
	dsbd.guid3DAlgorithm = guid3DAlgorithm;
	dsbd.lpwfxFormat = pWaveFile->m_pwfx;

	// DirectSound is only guarenteed to play PCM data.  Other
	// formats may or may not work depending the sound card driver.
	hr = G_SoundManager->CreateSoundBuffer(&dsbd, &apDSBuffer[0], NULL);

	// Be sure to return this error code if it occurs so the
	// callers knows this happened.
	if (hr == DS_NO_VIRTUALIZATION)
		hrRet = DS_NO_VIRTUALIZATION;

	if (FAILED(hr))
	{
		// DSERR_BUFFERTOOSMALL will be returned if the buffer is
		// less than DSBSIZE_FX_MIN and the buffer is created
		// with DSBCAPS_CTRLFX.

		// It might also fail if hardware buffer mixing was requested
		// on a device that doesn't support it.
		DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);

		goto LFail;
	}

	// Default to use DuplicateSoundBuffer() when created extra buffers since always 
	// create a buffer that uses the same memory however DuplicateSoundBuffer() will fail if 
	// DSBCAPS_CTRLFX is used, so use CreateSoundBuffer() instead in this case.
	if ((dwCreationFlags & DSBCAPS_CTRLFX) == 0)
	{
		for (i = 1; i < dwNumBuffers; i++)
		{
			if (FAILED(hr = G_SoundManager->DuplicateSoundBuffer(apDSBuffer[0], &apDSBuffer[i])))
			{
				DXTRACE_ERR(TEXT("DuplicateSoundBuffer"), hr);
				goto LFail;
			}
		}
	}
	else
	{
		for (i = 1; i < dwNumBuffers; i++)
		{
			hr = G_SoundManager->CreateSoundBuffer(&dsbd, &apDSBuffer[i], NULL);
			if (FAILED(hr))
			{
				DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);
				goto LFail;
			}
		}
	}

	// Create the sound
	*ppSound = new GSound(apDSBuffer, dwDSBufferSize, dwNumBuffers, pWaveFile, dwCreationFlags);

	SAFE_DELETE_ARRAY(apDSBuffer);
	return hrRet;

LFail:
	// Cleanup
	SAFE_DELETE_ARRAY(pWaveFile);
	SAFE_DELETE_ARRAY(apDSBuffer);
	return hr;
}

HRESULT CSoundManager::CreateFromMemory(GSound ** ppSound, BYTE * pbData, ULONG ulDataSize, LPWAVEFORMATEX pwfx, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNumBuffers)
{
	HRESULT hr;
	DWORD   i;
	LPDIRECTSOUNDBUFFER* apDSBuffer = NULL;
	DWORD                dwDSBufferSize = NULL;
	CWaveFile*           pWaveFile = NULL;

	if (G_SoundManager == NULL)
		return CO_E_NOTINITIALIZED;
	if (pbData == NULL || ppSound == NULL || dwNumBuffers < 1)
		return E_INVALIDARG;

	apDSBuffer = new LPDIRECTSOUNDBUFFER[dwNumBuffers];
	if (apDSBuffer == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto LFail;
	}

	pWaveFile = new CWaveFile();
	if (pWaveFile == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto LFail;
	}

	pWaveFile->OpenFromMemory(pbData, ulDataSize, pwfx, WAVEFILE_READ);


	// Make the DirectSound buffer the same size as the wav file
	dwDSBufferSize = ulDataSize;

	// Create the direct sound buffer, and only request the flags needed
	// since each requires some overhead and limits if the buffer can 
	// be hardware accelerated
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = dwCreationFlags;
	dsbd.dwBufferBytes = dwDSBufferSize;
	dsbd.guid3DAlgorithm = guid3DAlgorithm;
	dsbd.lpwfxFormat = pwfx;

	if (FAILED(hr = G_SoundManager->CreateSoundBuffer(&dsbd, &apDSBuffer[0], NULL)))
	{
		DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);
		goto LFail;
	}

	// Default to use DuplicateSoundBuffer() when created extra buffers since always 
	// create a buffer that uses the same memory however DuplicateSoundBuffer() will fail if 
	// DSBCAPS_CTRLFX is used, so use CreateSoundBuffer() instead in this case.
	if ((dwCreationFlags & DSBCAPS_CTRLFX) == 0)
	{
		for (i = 1; i < dwNumBuffers; i++)
		{
			if (FAILED(hr = G_SoundManager->DuplicateSoundBuffer(apDSBuffer[0], &apDSBuffer[i])))
			{
				DXTRACE_ERR(TEXT("DuplicateSoundBuffer"), hr);
				goto LFail;
			}
		}
	}
	else
	{
		for (i = 1; i < dwNumBuffers; i++)
		{
			hr = G_SoundManager->CreateSoundBuffer(&dsbd, &apDSBuffer[i], NULL);
			if (FAILED(hr))
			{
				DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);
				goto LFail;
			}
		}
	}

	// Create the sound
	*ppSound = new GSound(apDSBuffer, dwDSBufferSize, dwNumBuffers, pWaveFile, dwCreationFlags);

	SAFE_DELETE_ARRAY(apDSBuffer);
	return S_OK;

LFail:
	// Cleanup

	SAFE_DELETE_ARRAY(apDSBuffer);
	return hr;
}

HRESULT CSoundManager::CreateStreaming(GStreamingSound ** ppStreamingSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNotifyCount, DWORD dwNotifySize, HANDLE hNotifyEvent)
{
	HRESULT hr;

	if (G_SoundManager == NULL)
		return CO_E_NOTINITIALIZED;
	if (strWaveFileName == NULL || ppStreamingSound == NULL || hNotifyEvent == NULL)
		return E_INVALIDARG;

	LPDIRECTSOUNDBUFFER pDSBuffer = NULL;
	DWORD               dwDSBufferSize = NULL;
	CWaveFile*          pWaveFile = NULL;
	DSBPOSITIONNOTIFY*  aPosNotify = NULL;
	LPDIRECTSOUNDNOTIFY pDSNotify = NULL;

	pWaveFile = new CWaveFile();
	if (pWaveFile == NULL)
		return E_OUTOFMEMORY;
	pWaveFile->Open(strWaveFileName, NULL, WAVEFILE_READ);

	// Figure out how big the DSound buffer should be 
	dwDSBufferSize = dwNotifySize * dwNotifyCount;

	// Set up the direct sound buffer.  Request the NOTIFY flag, so
	// that we are notified as the sound buffer plays.  Note, that using this flag
	// may limit the amount of hardware acceleration that can occur. 
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = dwCreationFlags |
		DSBCAPS_CTRLPOSITIONNOTIFY |
		DSBCAPS_GETCURRENTPOSITION2;
	dsbd.dwBufferBytes = dwDSBufferSize;
	dsbd.guid3DAlgorithm = guid3DAlgorithm;
	dsbd.lpwfxFormat = pWaveFile->m_pwfx;

	if (FAILED(hr = G_SoundManager->CreateSoundBuffer(&dsbd, &pDSBuffer, NULL)))
	{
		// If wave format isn't then it will return 
		// either DSERR_BADFORMAT or E_INVALIDARG
		if (hr == DSERR_BADFORMAT || hr == E_INVALIDARG)
			return DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);

		return DXTRACE_ERR(TEXT("CreateSoundBuffer"), hr);
	}

	// Create the notification events, so that we know when to fill
	// the buffer as the sound plays. 
	if (FAILED(hr = pDSBuffer->QueryInterface(IID_IDirectSoundNotify,
		(VOID**)&pDSNotify)))
	{
		SAFE_DELETE_ARRAY(aPosNotify);
		return DXTRACE_ERR(TEXT("QueryInterface"), hr);
	}

	aPosNotify = new DSBPOSITIONNOTIFY[dwNotifyCount];
	if (aPosNotify == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < dwNotifyCount; i++)
	{
		aPosNotify[i].dwOffset = (dwNotifySize * i) + dwNotifySize - 1;
		aPosNotify[i].hEventNotify = hNotifyEvent;
	}

	// Tell DirectSound when to notify us. The notification will come in the from 
	// of signaled events that are handled in WinMain()
	if (FAILED(hr = pDSNotify->SetNotificationPositions(dwNotifyCount,
		aPosNotify)))
	{
		SAFE_RELEASE(pDSNotify);
		SAFE_DELETE_ARRAY(aPosNotify);
		return DXTRACE_ERR(TEXT("SetNotificationPositions"), hr);
	}

	SAFE_RELEASE(pDSNotify);
	SAFE_DELETE_ARRAY(aPosNotify);

	// Create the sound
	*ppStreamingSound = new GStreamingSound(pDSBuffer, dwDSBufferSize, pWaveFile, dwNotifySize);

	return S_OK;
}

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "StaticObject.h"
#include "Simon.h"
#include <map>
#include "GAudio.h"

class CSoundManager
{
public:
	static CSoundManager *GetInstance();
	GSound* LoadSound(char *filename);
	void AddSoundToList(int a_index, GSound* a_sound);
	void PlaySoundWithIndex(int a_index);
	void LoopSoundWithIndex(int a_index);
	void StopSoundWithIndex(int a_index);
	bool Init();
	void Release();
	void LoadAllSounds();
protected:
	HRESULT SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate);
	HRESULT Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener);
	HRESULT Create(GSound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
	HRESULT CreateFromMemory(GSound** ppSound, BYTE* pbData, ULONG ulDataSize, LPWAVEFORMATEX pwfx, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
	HRESULT CreateStreaming(GStreamingSound** ppStreamingSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNotifyCount, DWORD dwNotifySize, HANDLE hNotifyEvent);
	static CSoundManager *_instance;
	std::map<int, GSound*> _listOfSounds;
	CSoundManager();
};
#endif //!__SOUND_MANAGER_H__
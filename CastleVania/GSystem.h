#ifndef __GSYSTEM_H__
#define __GSYSTEM_H__

#include <windows.h>
#include <d3d9.h>
#include "Global.h"
#include <dinput.h>
#include "GScene.h"

class TiXmlElement;

class GSystem
{
public:
	static GSystem *GetInstance();

	void Init();

	void Run();

	void Release();

	void Set_nCmdShow(int a_nCmdShow);

	DWORD GetDeltaTime();
	DWORD GetNowTime();
private:
	bool _paused;
	DWORD _durationBeforeNow;
	DWORD _nowBeforePaused;
	DWORD _elapsedTime;
	DWORD _now;
	GSystem();
	static GSystem *_instance;
	int _nCmdShow;
	DWORD _DeltaTime;
protected:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool loadDataFromFile(const char * path);
	bool loadGameInfoFromXml(TiXmlElement*);
	bool loadAllTextureFromXml(TiXmlElement*);
	int InitWindow(int nCmdShow);

	bool InitDirectX();
	void ReleaseDirectX();

	void draw();

	int _screenWidth;
	int _screenHeight;
	char *_gameTitle;
	bool _isFullScreen;
	int _gameRate;
};
#endif //!__GSYSTEM_H__
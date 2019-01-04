#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <d3d9.h>
#include "Global.h"
#include <dinput.h>

class CGame
{
public:
	CGame(int _nCmdShow);	

	void InitGame();

	void GameRun();

	void GameEnd();


protected:
	virtual void RenderFrame();

	int nCmdShow;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int InitWindow(int nCmdShow);

	int InitDirectX();
	void ReleaseDirectX();

	void InitDirectInput();

	void InitKeyboard();
	void InitMouse();

	void ReleaseKeyboard();
	void ReleaseMouse();

	void ProcessKeyboard();
	void ProcessMouse();

	virtual void LoadResources();
	virtual void ProcessInput();
	virtual void Update();

	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);

	int IsKeyDown(int KeyCode);
	int MouseButton(int Button);
	int GetMouseX();
	int GetMouseY();

	void GameDraw();

	DWORD _DeltaTime;

	BYTE  _KeyStates[256]; // DirectInput keyboard state buffer 

	DIDEVICEOBJECTDATA _KeyEvents[ GL_KEY_BUFFER_SIZE ]; // Buffered keyboard data
};

#endif
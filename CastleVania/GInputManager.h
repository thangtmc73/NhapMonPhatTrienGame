#ifndef __GINPUT_MANAGER_H__
#define __GINPUT_MANAGER_H__

#include <dinput.h>
#include "Global.h"

class GInputManager
{
public:
	static GInputManager *GetInstance();
	bool Init();
	void Release();
	int IsKeyDown(int Key);
	int IsKeyPressed(int Key);
	int MouseButton(int Button);
	int GetMouseX();
	int GetMouseY();
	void RetrieveData();
	void ProcessKeyboard();
private:
	static GInputManager* _instance;
	bool InitDirectInput();
	void ReleaseDirectInput();

	void InitKeyboard();
	void InitMouse();

	void ProcessMouse();
	void ProcessInput();

	void Reset();

	void ReleaseKeyboard();
	void ReleaseMouse();
	void OnKeyDown(unsigned int keyCode);
	bool  _KeyMap[1024];
	BYTE  _KeyStates[256]; // DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA _KeyEvents[GL_KEY_BUFFER_SIZE]; // Buffered keyboard data

	GInputManager();
	~GInputManager();
};

#endif //!__GINPUT_MANAGER_H__
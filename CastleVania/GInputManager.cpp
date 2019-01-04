#include "GInputManager.h"
#include "dxutil.h"

GInputManager* GInputManager::_instance = NULL;

GInputManager * GInputManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new GInputManager();
	}
	return _instance;
}

bool GInputManager::Init()
{
	if (!InitDirectInput())
	{
		MessageBox(G_hWnd, "Error initializing DirectInput", "Error", MB_OK);
		return false;
	}
	InitKeyboard();
	InitMouse();
	return true;
	
}

void GInputManager::Release()
{
	ReleaseKeyboard();
	ReleaseMouse();
	ReleaseDirectInput();
}

bool GInputManager::InitDirectInput()
{
	HRESULT
		hr = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(VOID**)&G_DirectInput,
			NULL
		);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
	{
		return false;
	}

	////initialize the mouse
	hr = G_DirectInput->CreateDevice(GUID_SysMouse, &G_Mouse, NULL);

	//// TO-DO: put in exception handling
	if (FAILED(hr) == true)
	{
		return false;
	}

	hr = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
	{
		return false;
	}

	return true;
}

void GInputManager::ReleaseDirectInput()
{
	if (G_DirectInput != NULL)
	{
		SAFE_RELEASE(G_DirectInput);
	}
}

void GInputManager::InitKeyboard()
{
	HRESULT hr;
	hr = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr) == true)
	{
		return;
	}

	hr = G_KeyBoard->SetCooperativeLevel(G_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr) == true)
	{
		return;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = GL_KEY_BUFFER_SIZE;

	hr = G_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr) == true)
	{
		return;
	}
	
	hr = G_KeyBoard->Acquire();
	if (FAILED(hr) == true)
	{
		return;
	}
}

void GInputManager::InitMouse()
{
	HRESULT hr = G_Mouse->SetDataFormat(&c_dfDIMouse);

	if (FAILED(hr) == true)
	{
		return;
	}

	hr = G_Mouse->SetCooperativeLevel(G_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

	if (FAILED(hr) == true)
	{
		return;
	}

	hr = G_Mouse->Acquire();

	if (FAILED(hr) == true)
	{
		return;
	}
}

void GInputManager::ReleaseKeyboard()
{
	if (G_KeyBoard != NULL)
	{
		G_KeyBoard->Unacquire();
		SAFE_RELEASE(G_KeyBoard);
	}
}

void GInputManager::ReleaseMouse()
{
	if (G_Mouse != NULL)
	{
		G_Mouse->Unacquire();
		SAFE_RELEASE(G_KeyBoard);
	}
}

void GInputManager::OnKeyDown(unsigned int keyCode)
{
	_KeyMap[keyCode] = true;
}

void GInputManager::ProcessKeyboard()
{
	ZeroMemory(_KeyStates, sizeof(_KeyStates));
	HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	if (hr != S_OK)
	{
		hr = G_KeyBoard->Acquire();
		G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	}

	// Collect all key states first
	G_KeyBoard->GetDeviceState(sizeof(_KeyStates), &_KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(G_hWnd, WM_QUIT, 0, 0);
	}
	Reset();

	// Collect all buffered events
	DWORD dwElements = GL_KEY_BUFFER_SIZE;
	hr = G_KeyBoard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		unsigned int KeyCode = (unsigned int)_KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) != 0)
		{
			int k = i;
			//OnKeyDown(KeyCode);
		}
		else
		{
			//OnKeyUp(KeyCode);
		}
	}
}

void GInputManager::ProcessMouse()
{
	ZeroMemory(&G_MouseState, sizeof(G_MouseState));
	HRESULT hr = G_Mouse->GetDeviceState(sizeof(G_MouseState), (LPVOID)&G_MouseState);
	if (hr != S_OK)
	{
		hr = G_Mouse->Acquire();
		G_Mouse->GetDeviceState(sizeof(G_MouseState), (LPVOID)&G_MouseState);
	}
	// Collect all key states first
	G_Mouse->GetDeviceState(sizeof(G_MouseState), &G_MouseState);

	//check for mouse button (to exit program)
	/*if (MouseButton(0))
	{
		PostMessage(G_hWnd, WM_DESTROY, 0, 0);
	}*/

	// Collect all buffered events

}

void GInputManager::ProcessInput()
{
}

void GInputManager::Reset()
{
	for (int i = 0; i < 1024; i++)
	{
		_KeyMap[i] = false;
	}
}

int GInputManager::IsKeyDown(int keyCode)
{
	return (_KeyStates[keyCode] & 0x80) != 0;
}

int GInputManager::IsKeyPressed(int Key)
{
	if (_KeyMap[Key] == true)
	{
		int a = 0;
	}
	return _KeyMap[Key];
}

int GInputManager::MouseButton(int Button)
{
	return (G_MouseState.rgbButtons[Button] & 0x80) > 0;
}

int GInputManager::GetMouseX()
{
	return G_MouseState.lX;
}

int GInputManager::GetMouseY()
{
	return G_MouseState.lY;
}

void GInputManager::RetrieveData()
{
	ProcessKeyboard();
	ProcessMouse();
}

GInputManager::GInputManager()
{
	G_KeyBoard = NULL;
	G_Mouse = NULL;
}

GInputManager::~GInputManager() { }



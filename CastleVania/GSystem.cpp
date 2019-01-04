#include <windows.h>
#include <d3d9.h>
#include "GSystem.h"
#include "GInputManager.h"
#include "SoundManager.h"
#include "dsutil.h"
#include <windows.h>
#include "SceneManager.h"
#include "Log.h"
#include "TinyXML/tinyxml.h"
#include "TextureManager.h"
#include "Resources.h"

GSystem* GSystem::_instance = NULL;

int GSystem::InitWindow(int nCmdShow)
{
	Resources* resource = Resources::getInstance();
	std::string gameTitle = Resources::getInstance()->getStringConstWithName("game-title");

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = G_hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = gameTitle.c_str();
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	int windowStyle;
	if (Resources::getInstance()->getIntegerConstWithName("is-full-screen") != 0) {
		windowStyle = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; // the fullscreen mode
	}
	else {
		windowStyle = WS_OVERLAPPEDWINDOW; // the window mode
	}
	int a = Resources::getInstance()->getIntegerConstWithName("window-width");
	int b = Resources::getInstance()->getIntegerConstWithName("window-height");

	G_hWnd =
		CreateWindow(
			gameTitle.c_str(),
			gameTitle.c_str(),
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			Resources::getInstance()->getIntegerConstWithName("window-width"),
			Resources::getInstance()->getIntegerConstWithName("window-height"),
			NULL,
			NULL,
			G_hInstance,
			NULL);

	if (!G_hWnd)
	{
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(G_hWnd, nCmdShow);
	UpdateWindow(G_hWnd);
	return true;
}

bool GSystem::InitDirectX()
{
	Resources* resource = Resources::getInstance();

	G_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (Resources::getInstance()->getIntegerConstWithName("is-full-screen") == 0) {
		d3dpp.Windowed = TRUE;
	}
	else {
		d3dpp.Windowed = FALSE;
	}


	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = Resources::getInstance()->getIntegerConstWithName("window-height");
	d3dpp.BackBufferWidth = Resources::getInstance()->getIntegerConstWithName("window-width");

	G_DirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		G_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&G_Device);

	if (G_Device == NULL)
	{
		return false;
	}
	
	//backbuffer
	G_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &G_BackBuffer);

	//sprite handler
	D3DXCreateSprite(G_Device, &G_SpriteHandler);

	return true;
}

void GSystem::ReleaseDirectX()
{
	if (G_Device != NULL)
	{
		G_Device->Release();
	}
	if (G_DirectX != NULL)
	{
		G_DirectX->Release();
	}
}

void GSystem::Init()
{
	InitWindow(_nCmdShow);
	InitDirectX();
	GInputManager::GetInstance()->Init();
	CSoundManager::GetInstance()->Init();
	CSoundManager::GetInstance()->LoadAllSounds();
	GSceneManager::GetInstance()->Init();
	Log::getInstance()->init();
	loadDataFromFile("game_config.xml");
}

// Main game message loop
void GSystem::Run()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 1000 / Resources::getInstance()->getIntegerConstWithName("frame-rate");

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_now = GetTickCount();

		_DeltaTime = _now - frame_start;
		GInputManager::GetInstance()->RetrieveData();

		GSceneManager::GetInstance()->GetCurrentScene()->ProcessInput();
		if (_DeltaTime >= tick_per_frame)
		{
			GSceneManager::GetInstance()->update(_DeltaTime);

			frame_start = _now;

		}
		draw();

	}
}

void GSystem::draw()
{
	if (G_Device->BeginScene())
	{
		// Clear back buffer with BLACK
		G_Device->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//----- start drawing
		GSceneManager::GetInstance()->GetCurrentScene()->RenderFrame();
		//---- end drawing
		G_SpriteHandler->End();
		G_Device->EndScene();
	}

	G_Device->Present(NULL, NULL, NULL, NULL);
}

void GSystem::Release()
{
	GInputManager::GetInstance()->Release();
	CSoundManager::GetInstance()->Release();
	ReleaseDirectX();
	Log::getInstance()->release();
}

LRESULT CALLBACK GSystem::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool GSystem::loadDataFromFile(const char * path)
{
	Resources::getInstance()->loadTexturesFromTextureInfo();
	if (path != NULL)
	{
		TiXmlDocument doc(path);
		bool success = doc.LoadFile();
		if (success)
		{
			//TiXmlElement* root = doc.FirstChildElement();
			TiXmlElement* root = doc.RootElement();
			for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
			{
				const char *value = elem->Value();
				std::string nodeName = value;
				if (nodeName == "window") {
					loadGameInfoFromXml(elem);
				}
				if (nodeName == "textures") {
					loadAllTextureFromXml(elem);
				}
			}
		}
		else
		{
			doc.ErrorDesc();
			//assert(success == true, "Load the configurations file failed");
			return false;
		}
	}
	return true;
	return false;
}

bool GSystem::loadGameInfoFromXml(TiXmlElement* node)
{
	for (TiXmlNode* elem = node->FirstChild(); elem != NULL; elem = elem->NextSibling())
	{
		const char* name = elem->Value();
		std::string keyName = name;
		if (keyName == "game-title") {
			const char *value = elem->FirstChild()->Value();
			_gameTitle = new char[sizeof(value) + 1];
			strcpy(_gameTitle, value);
		}
		if (keyName == "is-full-screen") {
			const char *value = elem->FirstChild()->Value();
			char *result;
			result = new char[sizeof(value) + 1];
			strcpy(result, value);
			int isFull = std::atoi(result);
			if (isFull == 0) {
				_isFullScreen = false;
			}
			else {
				_isFullScreen = true;
			}
		}
		if (keyName == "window-height") {
			const char *value = elem->FirstChild()->Value();
			char *result;
			result = new char[sizeof(value) + 1];
			strcpy(result, value);
			_screenHeight = std::atoi(result);
		}
		if (keyName == "window-width") {
			const char *value = elem->FirstChild()->Value();
			char *result;
			result = new char[sizeof(value) + 1];
			strcpy(result, value);
			_screenWidth = std::atoi(result);
		}
		if (keyName == "frame-rate") {
			const char *value = elem->FirstChild()->Value();
			char *result;
			result = new char[sizeof(value) + 1];
			strcpy(result, value);
			_gameRate = std::atoi(result);
		}
	}
	return true;
}

bool GSystem::loadAllTextureFromXml(TiXmlElement *node)
{
	TextureManager::getInstance()->loadFromXml(node);
	return false;
}

GSystem * GSystem::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new GSystem();
	}
	return _instance;
}

void GSystem::Set_nCmdShow(int a_nCmdShow)
{
	_nCmdShow = a_nCmdShow;
}

DWORD GSystem::GetDeltaTime()
{
	return _DeltaTime;
}

DWORD GSystem::GetNowTime()
{
	return _now;
}

GSystem::GSystem()
{
	//_paused = false;
	//_durationBeforeNow = 0;
	//_elapsedTime = 0;*/
}
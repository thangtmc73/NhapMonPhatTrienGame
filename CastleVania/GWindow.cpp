#include "GWindow.h"
#include "Global.h"

GWindow * GWindow::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new GWindow();
	}
	return _instance;
}

bool GWindow::Init()
{
	
	return false;
}

void GWindow::Release()
{
}

LRESULT CALLBACK GWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

int GWindow::InitWindow(int nCmdShow)
{
	return 0;
}

bool GWindow::InitDirectX()
{
	G_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (G_IsFullScreen) {
		d3dpp.Windowed = FALSE;
	}
	else {
		d3dpp.Windowed = TRUE;
	}

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = G_ScreenHeight;
	d3dpp.BackBufferWidth = G_ScreenWidth;

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

void GWindow::ReleaseDirectX()
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


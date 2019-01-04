#include <windows.h>
#include <d3d9.h>
#include "GScene.h"

GScene::GScene() {}

void GScene::RenderFrame()
{
	G_Device->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
}

void GScene::Init()
{
	LoadResources();
}

void GScene::Release()
{
}

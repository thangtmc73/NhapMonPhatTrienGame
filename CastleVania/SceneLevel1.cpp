#include "SceneLevel1.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"


SceneLevel1::SceneLevel1() {}

void SceneLevel1::RenderFrame()
{
	//_simon->SetX(_simon->GetX() - 1);
	//D3DXVECTOR2 pos = a_camera->Transform(_x, _y);
	
	_bg->Draw(0, 0, _camera->viewport.x, 0, G_ScreenWidth, 320);
	//_bg->DrawAllTheMap(0, 0);
	_simon->DrawWithCamera(_camera);
	//_simon->DrawWhip();
	_ghoul->Draw();
	//Resource.
	_spearKnight->Draw();
	_panther->Draw();
}

void SceneLevel1::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
	/*if (left)
	{
		_camera->UpdateCamera(_DeltaTime, 0);
	}
	if (GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		_camera->UpdateCamera(_DeltaTime);
	}*/
}

void SceneLevel1::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("state1map1BG.txt");
	_bg->LoadImageFromFile("state1map1TS.png");
	_bg->SetArrayDimensions(48, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(7);
	_bg->SetNumberRows(7);
	_bg->SetNumberOfTiles(49);
	_simon = new CSimon(SIMON_X, SIMON_Y);
	_ghoul = new CGhoul(110, 260);
	_spearKnight = new CSpearKnight(140, 260);
	_panther = new CPanther(220, 280);
	_camera = new GCamera();
	_camera->SetSizeMap(1536, G_ScreenWidth);
	_camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
	//_quadTree = new GQuadtree();
}

void SceneLevel1::Update(int a_delta_time)
{
	//_quadTree->Clear();
	
	_simon->MakeAnimation(a_delta_time);
	_spearKnight->MakeAnimation(a_delta_time);
	_ghoul->MakeAnimation(a_delta_time);
	_panther->MakeAnimation(a_delta_time);
	//_spearKnight->Update();
	//_ghoul->Update();
	_simon->Update(a_delta_time);
	//_panther->Update();
	_camera->UpdateCamera(_simon->GetX());
}


SceneLevel1::~SceneLevel1(void)
{
}
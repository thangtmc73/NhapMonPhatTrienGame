#include "SceneLevel1Stage1.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "ObjectManager.h"
#include "StatusBar.h"

SceneLevel1Stage1::SceneLevel1Stage1() {}

void SceneLevel1Stage1::RenderFrame()
{
	//_simon->SetX(_simon->GetX() - 1);
	//D3DXVECTOR2 pos = a_camera->Transform(_x, _y);
	//if (_simon->GetX() < 2600)
	//{
	//	_bg->DrawWithCamera(0, 0, _camera->viewport.x, 0, G_ScreenWidth, 320);
	//	//_bg->DrawAllTheMap(0, 0);
	//	_simon->DrawWithCamera(_camera);
	//}//_simon->DrawWhip();
	//else
	//{
	//	_bg->DrawWithCamera(0, 0, _camera->viewport.x, 0, G_ScreenWidth, 320);
	//	_simon->DrawWithCamera(_camera);
	//}
	if (_simon->GetX() < _camera->GetMaxSize() - 150)
	{
		_bg->DrawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth, 320);
		CObjectManager::GetInstance()->DrawAllObjectsWithCamera(_camera);
		_ground->DrawWithCamera(16, 106, _camera, G_ScreenWidth);
		_simon->DrawWithCamera(_camera);
	}
	else
	{
		_bg->DrawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth - 96, 320);
		CObjectManager::GetInstance()->DrawAllObjectsWithCamera(_camera);
		_bg->DrawApartOfTheMap(G_ScreenWidth - 96, 69, 44, 46, 0, 9);
		_ground->DrawWithCamera(16, 106, _camera, G_ScreenWidth);
		_simon->DrawWithCamera(_camera);
	}
	CStatusBar::GetInstance()->Draw();
	//_ground->Draw();
	//_ghoul->Draw();
	//Resource.
	//_spearKnight->Draw();
	//_panther->Draw();
}

void SceneLevel1Stage1::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void SceneLevel1Stage1::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("state1map1BG.txt");
	_bg->LoadImageFromFile("state1map1TS.png");
	CObjectManager::GetInstance()->GetObjectsFromFile("state1map1GO.txt");
	_bg->SetArrayDimensions(47, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(7);
	_bg->SetNumberRows(7);
	_bg->SetNumberOfTiles(48);
	_simon = new CSimon(SIMON_X, 180);
	/*_ghoul = new CGhoul(110, 260);
	_spearKnight = new CSpearKnight(140, 260);
	_panther = new CPanther(220, 280);*/
	_camera = new GCamera();
	_camera->SetSizeMap(1536, G_ScreenWidth);
	_camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
	_ground = new CGround(0, 106, 0, 1536);
	//_quadTree = new GQuadtree();
}

void SceneLevel1Stage1::Update(int a_deltaTime)
{
	//_quadTree->Clear();
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	//_spearKnight->Update(a_deltaTime);
	//_ghoul->Update(a_deltaTime);
	_simon->Update(a_deltaTime);
	_simon->InteractWithGround(_ground);
	//_panther->Update(a_deltaTime);
	_camera->UpdateCamera(_simon->GetX());
}


SceneLevel1Stage1::~SceneLevel1Stage1(void)
{}
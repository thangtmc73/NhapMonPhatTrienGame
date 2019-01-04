#include "SceneLevel1Scene4.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "ObjectManager.h"

SceneLevel1Scene4::SceneLevel1Scene4() {}

void SceneLevel1Scene4::RenderFrame()
{
	//_simon->SetX(_simon->GetX() - 1);
	//D3DXVECTOR2 pos = a_camera->Transform(_x, _y);

	_bg->DrawWithCamera(0, 0, _camera->viewport.x, 0, G_ScreenWidth, 352);
	//_bg->DrawAllTheMap(0, 0);
	CObjectManager::GetInstance()->DrawAllObjectsWithCamera(_camera);
	//_simon->DrawWithCamera(_camera);
	////_simon->DrawWhip();
	//_ghoul->Draw();
	////Resource.
	//_spearKnight->Draw();
	//_panther->Draw();
}

void SceneLevel1Scene4::ProcessInput()
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

void SceneLevel1Scene4::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("SceneLevel1Scene3BG.txt");
	_bg->LoadImageFromFile("statemapTS.png");
	CObjectManager::GetInstance()->GetObjectsFromFile("SceneLevel1Scene3GO.txt");
	_bg->SetArrayDimensions(55, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(156);
	_simon = new CSimon(SIMON_X, SIMON_Y);
	_ghoul = new CGhoul(110, 260);
	_spearKnight = new CSpearKnight(140, 260);
	_panther = new CPanther(220, 280);
	_camera = new GCamera();
	_camera->SetSizeMap(1792, G_ScreenWidth);
	_camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
	//_quadTree = new GQuadtree();
}

void SceneLevel1Scene4::Update(int a_deltaTime)
{
	//_quadTree->Clear();
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	_spearKnight->Update(a_deltaTime);
	_ghoul->Update(a_deltaTime);
	_simon->Update(a_deltaTime);
	_panther->Update(a_deltaTime);
	_camera->UpdateCamera(_simon->GetX());
}


SceneLevel1Scene4::~SceneLevel1Scene4(){}
#include "SceneLevel1Scene1.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "GSystem.h"
#include "ObjectManager.h"
#include "StatusBar.h"

bool left = false, right = false, attack = false;


SceneLevel1Scene1::SceneLevel1Scene1() {}

void SceneLevel1Scene1::RenderFrame()
{
	if (_simon->GetX() < _camera->GetMaxSize() - 150)
	{
		_bg->DrawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth,320);
		CObjectManager::GetInstance()->DrawAllObjectsWithCamera(_camera);
		_simon->DrawWithCamera(_camera);
		//Xét va chạm
		//_collision->CheckCollision(_simon, CObjectManager::GetInstance(),left, right,attack);

	}
	else
	{
		_bg->DrawWithCamera(0, 69, _camera->viewport.x, 0, G_ScreenWidth - 96, 320);
		CObjectManager::GetInstance()->DrawAllObjectsWithCamera(_camera);
		_simon->DrawWithCamera(_camera);
		_bg->DrawApartOfTheMap(G_ScreenWidth - 96, 69, 44, 46, 0, 9);
	}
	CStatusBar::GetInstance()->Draw();

	//_ghoul->Draw();
	//Resource.
	//_spearKnight->Draw();
	//_panther->Draw();
}

void SceneLevel1Scene1::ProcessInput()
{
	left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void SceneLevel1Scene1::LoadResources()
{
	_bg = new GTiledBG();
	_bg->GetMapFromFile("SceneLevel1Scene1BG.txt");
	_bg->LoadImageFromFile("statemapTS.png");
	CObjectManager::GetInstance()->GetObjectsFromFile("SceneLevel1Scene1GO.txt");
	_bg->SetArrayDimensions(47, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(7);
	_bg->SetNumberRows(7);
	_bg->SetNumberOfTiles(48);
	_simon = new CSimon(114, 183);
	/*_ghoul = new CGhoul(110, 260);
	_spearKnight = new CSpearKnight(140, 260);
	_panther = new CPanther(220, 280);*/
	_camera = new GCamera();
	_camera->SetSizeMap(1536, G_ScreenWidth);
	_camera->viewport.x = 0;
	_camera->viewport.y = G_ScreenHeight;
	//_quadTree = new GQuadtree();
	_collision = new Collision();
}

void SceneLevel1Scene1::Update(int a_deltaTime)
{
	//_quadTree->Clear();
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	//_spearKnight->Update(a_deltaTime);
	//_ghoul->Update(a_deltaTime);
	_simon->Update(a_deltaTime);
	//_panther->Update(a_deltaTime);
	_camera->UpdateCamera(_simon->GetX());
}


SceneLevel1Scene1::~SceneLevel1Scene1(void)
{}
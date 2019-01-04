#include "Stage3.h"
#include "Utils.h"
#include "GInputManager.h"
#include "ObjectConfig.h"
#include "Simon.h"
#include "ObjectManager.h"
#include "StatusBar.h"
#include "InfoManager.h"

Stage3::Stage3() {}

void Stage3::RenderFrame()
{
	_bg->drawWithCamera(0, 69, _camera->viewport.x, 0, 515, 320);
	CObjectManager::GetInstance()->drawAllObjectsWithCamera(_camera);
	_simon->drawWithCamera(_camera);
	CStatusBar::GetInstance()->draw();
}

void Stage3::ProcessInput()
{
	bool left = GInputManager::GetInstance()->IsKeyDown(DIK_LEFT);
	bool right = GInputManager::GetInstance()->IsKeyDown(DIK_RIGHT);
	bool jump = GInputManager::GetInstance()->IsKeyDown(DIK_X);
	bool down = GInputManager::GetInstance()->IsKeyDown(DIK_DOWN);
	bool up = GInputManager::GetInstance()->IsKeyDown(DIK_UP);
	bool attack = GInputManager::GetInstance()->IsKeyDown(DIK_RETURN);

	_simon->GetInputRelatingToSimon(left, right, up, down, jump, attack);
}

void Stage3::LoadResources()
{
	CInfoManager::GetInstance()->SetStage(3);
	_bg = new GTiledBG();
	_bg->GetMapFromFile("Stage3BG.txt");
	_bg->LoadImageFromFile("statemapTSLevel1.png");
	_simon = new CSimon(1300, 125, true);
	CObjectManager::GetInstance()->AddObject(0, _simon);
	CObjectManager::GetInstance()->GetObjectsFromFile("Stage3GO.txt");
	//_objectManager->GetGroundObjectsFromFile("Stage3GD.txt");
	_bg->SetArrayDimensions(55, 10);
	_bg->SetTileDimensions(32, 32);
	_bg->SetNumberColumns(13);
	_bg->SetNumberRows(12);
	_bg->SetNumberOfTiles(168);
	_camera = new GCamera();
	_camera->SetSizeMap(1536, 515);
	_camera->viewport.x = 0;
	_camera->_xStartCamera = 0;
	_camera->viewport.y = G_ScreenHeight;
	//_quadTree = new GQuadtree();
}

void Stage3::update(int a_deltaTime)
{
	//_quadTree->Clear();
	CObjectManager::GetInstance()->CollideEachOther(a_deltaTime);
	CObjectManager::GetInstance()->UpdateAllObjects(a_deltaTime);
	//_objectManager->CollideWith(_simon);
	CInfoManager::GetInstance()->SetNewPosition("simon", _simon->getBoundingBox().position);

	_camera->UpdateCamera(_simon->getX());
}


Stage3::~Stage3(void)
{
	delete _simon;
	delete _bg;
	delete _camera;
	CObjectManager::GetInstance()->Clear();
}